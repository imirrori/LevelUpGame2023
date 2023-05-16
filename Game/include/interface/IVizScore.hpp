#ifndef IVIZSCORE_HPP
#define IVIZSCORE_HPP

namespace Visual {
class IScore {
public:

  virtual ~IScore() = default;

  virtual void ShowScore(int score) = 0;
};
} // Visual

#endif // IVIZSCORE_HPP
