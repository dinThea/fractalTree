#ifndef TRIANGLE_BRANCH_H
#define TRIANGLE_BRANCH_H
#include <vector>
#include "branch.h"

class triangle_branch : public branch {
    public:
        triangle_branch( double minLength, double length, double width, double angle, branch* parent );
        triangle_branch( double minLength, double length, double width, double angle );
        virtual void subdivide();
};

#endif
