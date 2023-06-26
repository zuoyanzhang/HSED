#include <getresult.hpp>
double getULP(double x, double origin) {
	mpfr_t mpfr_origin, mpfr_oracle, mp1, mp2, mp3, mp4, mp5, mp6, mp7, mp8, mp9;
	mpfr_inits2(128, mpfr_origin, mpfr_oracle, mp1, mp2, mp3, mp4, mp5, mp6, mp7, mp8, mp9, (mpfr_ptr) 0);
	mpfr_set_d(mp1, x, MPFR_RNDN);
	mpfr_set_d(mp2, x, MPFR_RNDN);
	mpfr_mul(mp3, mp1, mp2, MPFR_RNDN);
	mpfr_set_d(mp4, x, MPFR_RNDN);
	mpfr_mul(mp5, mp3, mp4, MPFR_RNDN);
	mpfr_set_d(mp6, x, MPFR_RNDN);
	mpfr_set_d(mp7, 6.2309999999999999, MPFR_RNDN);
	mpfr_sub(mp8, mp6, mp7, MPFR_RNDN);
	mpfr_div(mp9, mp5, mp8, MPFR_RNDN);

	mpfr_set(mpfr_oracle, mp9, MPFR_RNDN);
	mpfr_set_d(mpfr_origin, origin, MPFR_RNDN);
	double ulp = computeULPDiff(mpfr_origin, mpfr_oracle);
	mpfr_clears(mpfr_origin, mpfr_oracle, mp1, mp2, mp3, mp4, mp5, mp6, mp7, mp8, mp9, (mpfr_ptr) 0);
	mpfr_free_cache();
	return ulp;
}
double getRelativeError(double x, double origin) {
	mpfr_t mpfr_origin, mpfr_oracle, mpfr_relative, mpfr_absolute, mp1, mp2, mp3, mp4, mp5, mp6, mp7, mp8, mp9;
	mpfr_inits2(128, mpfr_origin, mpfr_oracle, mpfr_relative, mpfr_absolute, mp1, mp2, mp3, mp4, mp5, mp6, mp7, mp8, mp9, (mpfr_ptr) 0);
	mpfr_set_d(mp1, x, MPFR_RNDN);
	mpfr_set_d(mp2, x, MPFR_RNDN);
	mpfr_mul(mp3, mp1, mp2, MPFR_RNDN);
	mpfr_set_d(mp4, x, MPFR_RNDN);
	mpfr_mul(mp5, mp3, mp4, MPFR_RNDN);
	mpfr_set_d(mp6, x, MPFR_RNDN);
	mpfr_set_d(mp7, 6.2309999999999999, MPFR_RNDN);
	mpfr_sub(mp8, mp6, mp7, MPFR_RNDN);
	mpfr_div(mp9, mp5, mp8, MPFR_RNDN);

	mpfr_set(mpfr_oracle, mp9, MPFR_RNDN);
	mpfr_set_d(mpfr_origin, origin, MPFR_RNDN);
	mpfr_sub(mpfr_absolute, mpfr_oracle, mpfr_origin, MPFR_RNDN);
	mpfr_div(mpfr_relative, mpfr_absolute, mpfr_oracle, MPFR_RNDN);
	double relative = mpfr_get_d(mpfr_relative, MPFR_RNDN);
	relative = abs(relative);
	mpfr_clears(mpfr_origin, mpfr_oracle, mpfr_relative, mpfr_absolute, mp1, mp2, mp3, mp4, mp5, mp6, mp7, mp8, mp9, (mpfr_ptr) 0);
	mpfr_free_cache();
	return relative;
}
double getFloatToDoubleOfOrigin(const float &inputx) {
	double x = (double)inputx;
	return (x * x * x) / (x - 6.231);
}
double getDoubleOfOrigin(const double &inputx) {
	double x = inputx;
	return (x * x * x) / (x - 6.231);
}
double getFloatToDoubleOfOrigin2(const float &inputx) {
	double x = (double)inputx;
	return x;
}
double getDoubleOfOrigin2(const double &inputx) {
	double x = inputx;
	return x;
}
