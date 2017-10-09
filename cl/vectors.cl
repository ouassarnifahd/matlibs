kernel void vect_add(global double2 *vect1, global double2 *vect2, global double2* res, size_t size) {
    size_t i = get_global_id(0);
    res[i] = vect1[i] + vect2[i];
}

static local double2 complexe_mult(local double2 z1, local double2 z2) {
    // z1 * z2 = (a1 * a2 - b1 * b2) + i * (a1 * b2 + a2 * b1)
    double2 mult;
    mult.s0 = z1.s0 * z2.s0 - z1.s1 * z2.s1;
    mult.s1 = z1.s0 * z2.s1 + z1.s1 * z2.s0;
    return mult;
}

kernel void vect_cauchy_mult(global double2 *vect1, global double2 *vect2, global double2* res, size_t size)
