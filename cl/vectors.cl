kernel void vect_add(global double2 *vect1, global double2 *vect2, global double2* res, size_t size) {
    size_t i = get_global_id(0);
    res[i] = vect1[i] + vect2[i];
}

kernel void vect_mult(global double2 *vect1, global double2 *vect2, global double2* res, size_t size) {
    size_t i = get_global_id(0);
    res[i] = complexe_mult(vect1[i], vect2[i]);
}

kernel void vect_cauchy_mult(global double2 *vect1, global double2 *vect2, global double2* res, size_t size) {

}
