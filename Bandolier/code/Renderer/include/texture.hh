#ifndef BANDOLIER_TEXTURE_HH
#define BANDOLIER_TEXTURE_HH

#include <array>
#include <cstdint>
#include <string>
#include <memory>
#include <vector>

namespace Bandolier {

//!@TODO maybe should return 'dims' instead of specific sizes
// this will assist in supporting 1D, 2D, and 3D more easily
class Texture {
public:
  virtual
  ~Texture() = default;

  [[nodiscard]]
  virtual std::array<uint32_t, 3> Dims() const = 0;

  virtual void Bind(uint32_t slot) const = 0;
};

class Texture1D : public Texture {
public:
  static std::shared_ptr<Texture1D> Create(const std::vector<unsigned char>& data, unsigned int channels);
};

class Texture2D : public Texture {
public:
  static std::shared_ptr<Texture2D> Create(const std::string& path);
};

}

#endif //BANDOLIER_TEXTURE_HH
