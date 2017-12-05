static local double2 complexe_mult(local double2 z1, local double2 z2) {
    double2 mult;
    mult.s0 = z1.s0 * z2.s0 - z1.s1 * z2.s1;
    mult.s1 = z1.s0 * z2.s1 + z1.s1 * z2.s0;
    return mult;
}

static local double2 complexe_div(local double2 z1, local double2 z2) {
    double2 res_div;
    res_div.s0 = (z1.s0 * z2.s0 + z1.s1 * z2.s1)/(z2.s0 * z2.s0 + z2.s1 * z2.s1);
    res_div.s1 = (z1.s1 * z2.s0 - z1.s0 * z2.s1)/(z2.s0 * z2.s0 + z2.s1 * z2.s1);
    return res_div;
}

kernel void complexe_pow(global double2* z, size_t power, global double2* zpower) {
    *zpower = 
}
