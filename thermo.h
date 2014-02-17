#ifndef _THERMO_H_
#define _THERMO_H_
namespace MTL {

namespace details {

class Thermal_processor
{
public:
    static void DO_body_interaction_with_environment(int body_number);
    static void DO_body_interaction_inside(int body_number);
    static void DO_body_refresh_state(int body_number);
};
}
}

#endif // _THERMO_H_
