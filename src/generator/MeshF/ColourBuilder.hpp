#include "generator/MeshF/MeshStructs.hpp"
class ColourBuilder {
private:
  double rChanalCounter(Normal &normal);
  double gChanalCounter(double height, double min, double max);
  double bChanalCounter(double height, double seaLevel, double min);
  double aChanalCounter(unsigned index);

public:
  Colour colourCounter(unsigned index);
};