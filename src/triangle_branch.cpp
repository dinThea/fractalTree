#include <vector>
#define PI 3.1415
#include "triangle_branch.h"

triangle_branch::triangle_branch( double minLength, double length, double width, double angle, branch* parent ) :
    branch( minLength, length, width, angle, 0)
{
    
    if ( length > minLength ) this->subdivide();

}

triangle_branch::triangle_branch( double minLength, double length, double width, double angle ) :
    branch( minLength, length, width, angle, 0)
{
    this->subdivide();
}
                
void triangle_branch::subdivide() {

    branch* b1 = new triangle_branch( get_minLength(), get_length() / 2 , get_width() / 2,  get_angle(), this );
    branch* b2 = new triangle_branch( get_minLength(), get_length() / 2 , get_width() / 2,  get_angle() + PI*2/3, this );
    branch* b3 = new triangle_branch( get_minLength(), get_length() / 2 , get_width() / 2,  get_angle() - PI*2/3, this );

    this->push_back(b1);
    this->push_back(b2);
    this->push_back(b3);

}