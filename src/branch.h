#ifndef BRANCH_H
#define BRANCH_H
#include <vector>

class branch {
    public:
        branch( double minLength, double length, double width, double angle, branch* parent );
        branch( double minLength, double length, double width, double angle );
        virtual void subdivide();
        const double get_length();                 
        const double get_width();          
        const double get_level();        
        const double get_angle();                  
        std::vector<branch*> get_childs();   
        const branch* get_parent();                 
    private:
        std::vector<branch*> childs;
        branch* parent; 
        double minLength;
        double length;
        double width;
        double angle;
        double level;

};

#endif
