

#ifndef __I_FIG_TREE_H
#define __I_FIG_TREE_

/**
 * @brief 
 * 
 */
class IFigTree
{
public:
  IFigTree() {}
  virtual ~IFigTree() {}

  virtual bool Load() = 0;
  virtual bool Save() = 0;    // TODO: later?


private:

};


#endif