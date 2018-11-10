#include <vector>
#include <iostream>
#define PI 3.1415
#include "branch.h"

branch::branch( double minLength, double length, double width, double angle, branch* parent ) :
    minLength(minLength), length(length), width(width), angle(angle), parent(parent), level(parent->level + 1)
{   
    if ( length > minLength ) this->subdivide();

}

branch::branch( double minLength, double length, double width, double angle ) :
    minLength(minLength), length(length), width(width), angle(angle), level(0)
{
    this->subdivide();
}
                
const double branch::get_length                 () { return this->length;   }
const double branch::get_width                  () { return this->width;    }
const double branch::get_level                  () { return this->level;    }
const double branch::get_minLength              () { return this->minLength;}
const double branch::get_angle                  () { return this->angle;    }
std::vector<branch*> branch::get_childs         () { return this->childs;   }
const branch* branch::get_parent                () { return this->parent;   } 

void branch::subdivide() {

    double pwidth = width/2;
    if (pwidth < 1.0) { pwidth = 1.0; }
    branch* b1 = new branch( minLength, length / 1.3, pwidth, angle, this );
    branch* b2 = new branch( minLength, length / 1.8, pwidth, angle + PI/6, this );
    branch* b3 = new branch( minLength, length / 1.8, pwidth, angle - PI/6, this );

    childs.push_back(b1);
    childs.push_back(b2);
    childs.push_back(b3);

}

const void branch::push_back(branch* child) {
    childs.push_back(child);
}
