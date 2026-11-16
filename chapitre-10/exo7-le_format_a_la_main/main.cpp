#include <iostream>

#include <iomanip>

#include <sstream>

#include <vector>

#include <string>

#include <cstdint>

#include <cstring>

#include <cmath>

using namespace std;

class Reader {

    const vector<uint8_t>& data;

    size_t pos = 0;

public:

    Reader(const vector<uint8_t>& d) : data(d) {}

    bool readU8(uint8_t& v) {

        if (pos >= data.size()) return false;

        v = data[pos++];

        return true;

    }

    bool readU32(uint32_t& v) {

        if (data.size() - pos < 4) return false;

        v = uint32_t(data[pos])

          | (uint32_t(data[pos + 1]) << 8)

          | (uint32_t(data[pos + 2]) << 16)

          | (uint32_t(data[pos + 3]) << 24);

        pos += 4;

        return true;

    }

    bool readF32(float& v) {

        uint32_t bits;

        if (!readU32(bits)) return false;

        static_assert(sizeof(float) == 4, "float must be 32 bits");

        memcpy(&v, &bits, 4);

        return true;

    }

    bool skip(uint32_t n) {

        if (n > data.size() - pos) return false;

        pos += n;

        return true;

    }

};

string fmt(float value) {

    double rounded = round(static_cast<double>(value) * 100.0) / 100.0;

    if (rounded == 0.0) rounded = 0.0;

    ostringstream out;

    out << fixed << setprecision(2) << rounded;

    return out.str();

}

int main() {

    long long count;

    if (!(cin >> count) || count < 0) {

        cout << "TRONQUE\n";

        return 0;

    }

    vector<uint8_t> bytes;

    for (long long i = 0; i < count; ++i) {

        string token;

        if (!(cin >> token) || token.size() != 2) {

            cout << "TRONQUE\n";

            return 0;

        }

        unsigned int value;

        istringstream in(token);

        in >> hex >> value;

        if (!in || value > 255) {

            cout << "TRONQUE\n";

            return 0;

        }

        bytes.push_back(static_cast<uint8_t>(value));

    }

    if (bytes.size() < 4) {

        cout << "TRONQUE\n";

        return 0;

    }

    if (bytes[0] != 0x4E || bytes[1] != 0x4B ||

        bytes[2] != 0x52 || bytes[3] != 0x46) {

        cout << "PAS_UNE_PLANCHE\n";

        return 0;

    }

    Reader r(bytes);

    uint8_t ignored;

    uint32_t version;

    for (int i = 0; i < 4; ++i) {

        if (!r.readU8(ignored)) {

            cout << "TRONQUE\n";

            return 0;

        }

    }

    if (!r.readU32(version)) {

        cout << "TRONQUE\n";

        return 0;

    }

    if (version != 1) {

        cout << "VERSION_INCONNUE " << version << "\n";

        return 0;

    }

    float cx, cy, zoom;

    uint8_t theme, grid;

    if (!r.readF32(cx) || !r.readF32(cy) || !r.readF32(zoom) ||

        !r.readU8(theme) || !r.readU8(grid) ||

        !r.skip(2)) {

        cout << "TRONQUE\n";

        return 0;

    }

    uint32_t imageCount;

    if (!r.readU32(imageCount)) {

        cout << "TRONQUE\n";

        return 0;

    }

    ostringstream output;

    output << "VUE " << fmt(cx) << " " << fmt(cy)

           << " " << fmt(zoom) << "\n";

    output << "THEME " << (theme != 0 ? "SOMBRE" : "CLAIR") << "\n";

    output << "GRILLE " << (grid == 0 ? "AFFICHEE" : "CACHEE") << "\n";

    output << "IMAGES " << imageCount << "\n";

    for (uint32_t i = 1; i <= imageCount; ++i) {

        float x, y, scale, rotation, opacity;

        uint8_t mx, my;

        uint32_t width, height, size;

        if (!r.readF32(x) || !r.readF32(y) ||

            !r.readF32(scale) || !r.readF32(rotation) ||

            !r.readF32(opacity) ||

            !r.readU8(mx) || !r.readU8(my) ||

            !r.skip(2) ||

            !r.readU32(width) || !r.readU32(height) ||

            !r.readU32(size) || !r.skip(size)) {

            cout << "TRONQUE\n";

            return 0;

        }

        output << "IMAGE " << i << " "

               << fmt(x) << " " << fmt(y) << " "

               << fmt(scale) << " " << fmt(rotation) << " "

               << fmt(opacity) << " "

               << (mx != 0) << " " << (my != 0) << " "

               << width << " " << height << " " << size << "\n";

    }

    uint32_t strokeCount;

    if (!r.readU32(strokeCount)) {

        cout << "TRONQUE\n";

        return 0;

    }

    output << "TRAITS " << strokeCount << "\n";

    for (uint32_t i = 1; i <= strokeCount; ++i) {

        uint8_t red, green, blue, alpha;

        float thickness;

        uint32_t pointCount;

        if (!r.readU8(red) || !r.readU8(green) ||

            !r.readU8(blue) || !r.readU8(alpha) ||

            !r.readF32(thickness) || !r.readU32(pointCount)) {

            cout << "TRONQUE\n";

            return 0;

        }

        output << "TRAIT " << i << " "

               << unsigned(red) << " " << unsigned(green) << " "

               << unsigned(blue) << " " << unsigned(alpha) << " "

               << fmt(thickness) << " " << pointCount << "\n";

        for (uint32_t j = 1; j <= pointCount; ++j) {

            float x, y;

            if (!r.readF32(x) || !r.readF32(y)) {

                cout << "TRONQUE\n";

                return 0;

            }

            output << "POINT " << fmt(x) << " " << fmt(y) << "\n";

        }

    }

    cout << output.str();

    return 0;

}