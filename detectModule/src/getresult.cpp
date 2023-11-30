#include <getresult.hpp>
double getULP(double x, double origin) {
	mpfr_t mpfr_origin, mpfr_oracle, mp1, mp2, mp3, mp4, mp5, mp6, mp7, mp8, mp9, mp10, mp11, mp12, mp13, mp14, mp15, mp16, mp17, mp18, mp19, mp20, mp21, mp22, mp23, mp24, mp25, mp26, mp27, mp28, mp29;
	mpfr_inits2(128, mpfr_origin, mpfr_oracle, mp1, mp2, mp3, mp4, mp5, mp6, mp7, mp8, mp9, mp10, mp11, mp12, mp13, mp14, mp15, mp16, mp17, mp18, mp19, mp20, mp21, mp22, mp23, mp24, mp25, mp26, mp27, mp28, mp29, (mpfr_ptr) 0);
	mpfr_set_d(mp1, 1, MPFR_RNDN);
	mpfr_set_d(mp2, 0.5, MPFR_RNDN);
	mpfr_set_d(mp3, x, MPFR_RNDN);
	mpfr_mul(mp4, mp2, mp3, MPFR_RNDN);
	mpfr_add(mp5, mp1, mp4, MPFR_RNDN);
	mpfr_set_d(mp6, 0.125, MPFR_RNDN);
	mpfr_set_d(mp7, x, MPFR_RNDN);
	mpfr_mul(mp8, mp6, mp7, MPFR_RNDN);
	mpfr_set_d(mp9, x, MPFR_RNDN);
	mpfr_mul(mp10, mp8, mp9, MPFR_RNDN);
	mpfr_sub(mp11, mp5, mp10, MPFR_RNDN);
	mpfr_set_d(mp12, 0.0625, MPFR_RNDN);
	mpfr_set_d(mp13, x, MPFR_RNDN);
	mpfr_mul(mp14, mp12, mp13, MPFR_RNDN);
	mpfr_set_d(mp15, x, MPFR_RNDN);
	mpfr_mul(mp16, mp14, mp15, MPFR_RNDN);
	mpfr_set_d(mp17, x, MPFR_RNDN);
	mpfr_mul(mp18, mp16, mp17, MPFR_RNDN);
	mpfr_add(mp19, mp11, mp18, MPFR_RNDN);
	mpfr_set_d(mp20, 0.0390625, MPFR_RNDN);
	mpfr_set_d(mp21, x, MPFR_RNDN);
	mpfr_mul(mp22, mp20, mp21, MPFR_RNDN);
	mpfr_set_d(mp23, x, MPFR_RNDN);
	mpfr_mul(mp24, mp22, mp23, MPFR_RNDN);
	mpfr_set_d(mp25, x, MPFR_RNDN);
	mpfr_mul(mp26, mp24, mp25, MPFR_RNDN);
	mpfr_set_d(mp27, x, MPFR_RNDN);
	mpfr_mul(mp28, mp26, mp27, MPFR_RNDN);
	mpfr_sub(mp29, mp19, mp28, MPFR_RNDN);

	mpfr_set(mpfr_oracle, mp29, MPFR_RNDN);
	mpfr_set_d(mpfr_origin, origin, MPFR_RNDN);
	double ulp = computeULPDiff(mpfr_origin, mpfr_oracle);
	mpfr_clears(mpfr_origin, mpfr_oracle, mp1, mp2, mp3, mp4, mp5, mp6, mp7, mp8, mp9, mp10, mp11, mp12, mp13, mp14, mp15, mp16, mp17, mp18, mp19, mp20, mp21, mp22, mp23, mp24, mp25, mp26, mp27, mp28, mp29, (mpfr_ptr) 0);
	mpfr_free_cache();
	return ulp;
}
double getRelativeError(double x, double origin) {
	mpfr_t mpfr_origin, mpfr_oracle, mpfr_relative, mpfr_absolute, mp1, mp2, mp3, mp4, mp5, mp6, mp7, mp8, mp9, mp10, mp11, mp12, mp13, mp14, mp15, mp16, mp17, mp18, mp19, mp20, mp21, mp22, mp23, mp24, mp25, mp26, mp27, mp28, mp29;
	mpfr_inits2(128, mpfr_origin, mpfr_oracle, mpfr_relative, mpfr_absolute, mp1, mp2, mp3, mp4, mp5, mp6, mp7, mp8, mp9, mp10, mp11, mp12, mp13, mp14, mp15, mp16, mp17, mp18, mp19, mp20, mp21, mp22, mp23, mp24, mp25, mp26, mp27, mp28, mp29, (mpfr_ptr) 0);
	mpfr_set_d(mp1, 1, MPFR_RNDN);
	mpfr_set_d(mp2, 0.5, MPFR_RNDN);
	mpfr_set_d(mp3, x, MPFR_RNDN);
	mpfr_mul(mp4, mp2, mp3, MPFR_RNDN);
	mpfr_add(mp5, mp1, mp4, MPFR_RNDN);
	mpfr_set_d(mp6, 0.125, MPFR_RNDN);
	mpfr_set_d(mp7, x, MPFR_RNDN);
	mpfr_mul(mp8, mp6, mp7, MPFR_RNDN);
	mpfr_set_d(mp9, x, MPFR_RNDN);
	mpfr_mul(mp10, mp8, mp9, MPFR_RNDN);
	mpfr_sub(mp11, mp5, mp10, MPFR_RNDN);
	mpfr_set_d(mp12, 0.0625, MPFR_RNDN);
	mpfr_set_d(mp13, x, MPFR_RNDN);
	mpfr_mul(mp14, mp12, mp13, MPFR_RNDN);
	mpfr_set_d(mp15, x, MPFR_RNDN);
	mpfr_mul(mp16, mp14, mp15, MPFR_RNDN);
	mpfr_set_d(mp17, x, MPFR_RNDN);
	mpfr_mul(mp18, mp16, mp17, MPFR_RNDN);
	mpfr_add(mp19, mp11, mp18, MPFR_RNDN);
	mpfr_set_d(mp20, 0.0390625, MPFR_RNDN);
	mpfr_set_d(mp21, x, MPFR_RNDN);
	mpfr_mul(mp22, mp20, mp21, MPFR_RNDN);
	mpfr_set_d(mp23, x, MPFR_RNDN);
	mpfr_mul(mp24, mp22, mp23, MPFR_RNDN);
	mpfr_set_d(mp25, x, MPFR_RNDN);
	mpfr_mul(mp26, mp24, mp25, MPFR_RNDN);
	mpfr_set_d(mp27, x, MPFR_RNDN);
	mpfr_mul(mp28, mp26, mp27, MPFR_RNDN);
	mpfr_sub(mp29, mp19, mp28, MPFR_RNDN);

	mpfr_set(mpfr_oracle, mp29, MPFR_RNDN);
	mpfr_set_d(mpfr_origin, origin, MPFR_RNDN);
	mpfr_sub(mpfr_absolute, mpfr_oracle, mpfr_origin, MPFR_RNDN);
	mpfr_div(mpfr_relative, mpfr_absolute, mpfr_oracle, MPFR_RNDN);
	double relative = mpfr_get_d(mpfr_relative, MPFR_RNDN);
	relative = abs(relative);
	mpfr_clears(mpfr_origin, mpfr_oracle, mpfr_relative, mpfr_absolute, mp1, mp2, mp3, mp4, mp5, mp6, mp7, mp8, mp9, mp10, mp11, mp12, mp13, mp14, mp15, mp16, mp17, mp18, mp19, mp20, mp21, mp22, mp23, mp24, mp25, mp26, mp27, mp28, mp29, (mpfr_ptr) 0);
	mpfr_free_cache();
	return relative;
}
double getFloatToDoubleOfOrigin(const float &inputx) {
	double x = (double)inputx;
	return 1.0 + 0.5   * x - 0.125 * x * x + 0.0625 * x * x * x - 0.0390625 * x * x * x * x;
}
double getDoubleOfOrigin(const double &inputx) {
	double x = inputx;
	return 1.0 + 0.5   * x - 0.125 * x * x + 0.0625 * x * x * x - 0.0390625 * x * x * x * x;
}
double getFloatToDoubleOfOrigin2(const float &inputx) {
	double x = (double)inputx;
	return x;
}
double getDoubleOfOrigin2(const double &inputx) {
	double x = inputx;
	return x;
}
