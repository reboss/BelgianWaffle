#include "phys_cc1100.h"
#include "tcv.h"

#include "network_help.h"


void set_power(int sfd, int power) {
    tcv_control(sfd, PHYSOPT_SETPOWER, power);
}

