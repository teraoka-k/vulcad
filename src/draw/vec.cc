#if !defined(VULCAD_DRAW_VEC)
#define VULCAD_DRAW_VEC

class Vec {
public:
  float x;
  float y;
  float z;

  Vec(float _x = .0f, float _y = .0f, float _z = .0f) {
    x = _x;
    y = _y;
    z = _z;
  };

  Vec operator+(Vec v) { return Vec(x + v.x, y + v.y, z + v.z); };
  Vec operator-(Vec v) { return Vec(x - v.x, y - v.y, z - v.z); };
  Vec operator*(float scalar) {
    return Vec(x * scalar, y * scalar, z * scalar);
  };
  friend Vec operator*(float scalar, Vec v) { return v * scalar; };
  Vec operator/(float scalar) {
    return Vec(x / scalar, y / scalar, z / scalar);
  };
  bool operator==(const Vec v) { return x == v.x && y == v.y && z == v.z; };
};

#endif // VULCAD_DRAW_VEC