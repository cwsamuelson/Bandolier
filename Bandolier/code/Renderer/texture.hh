#ifndef BANDOLIER_TEXTURE_HH
#define BANDOLIER_TEXTURE_HH

#include <cstdint>
#include <string>
#include <memory>

namespace Bandolier {

class Texture
{
public:
  virtual
  ~Texture() = default;

  virtual uint32_t
  Width() const = 0;

  virtual uint32_t
  Height() const = 0;

  virtual void
  Bind(uint32_t slot) const = 0;
};

class Texture2D : public Texture
{
public:
  static std::shared_ptr<Texture2D>
  Create(const std::string& path);
};

}

#endif //BANDOLIER_TEXTURE_HH
