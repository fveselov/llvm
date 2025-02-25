// RUN: %clangxx -fsycl -fsyntax-only %s

#include <cassert>
#include <iostream>
#include <sycl/detail/common.hpp>
#include <sycl/half_type.hpp>
#include <sycl/sycl.hpp>

namespace s = sycl;
namespace d = sycl::detail;

using i_t = int;
using f_t = float;

namespace t {
using c_t = char;
using d_t = double;
} // namespace t

struct v {};

int main() {
  // is_floatn
  static_assert(d::is_floatn<s::vec<s::opencl::cl_float, 4>>::value == true);
  static_assert(d::is_floatn<s::vec<s::opencl::cl_float, 16>>::value == true);
  static_assert(d::is_floatn<s::float4>::value == true, "");
  static_assert(d::is_floatn<s::float16>::value == true, "");

  static_assert(d::is_floatn<s::opencl::cl_float>::value == false);
  static_assert(d::is_floatn<s::opencl::cl_int>::value == false);
  static_assert(d::is_floatn<i_t>::value == false, "");
  static_assert(d::is_floatn<f_t>::value == false, "");
  static_assert(d::is_floatn<t::c_t>::value == false, "");
  static_assert(d::is_floatn<t::d_t>::value == false, "");
  static_assert(d::is_floatn<v>::value == false, "");
  // is_genfloatf
  static_assert(d::is_genfloatf<s::vec<s::opencl::cl_float, 4>>::value == true);
  static_assert(d::is_genfloatf<s::vec<s::opencl::cl_float, 16>>::value == true);
  static_assert(d::is_genfloatf<s::opencl::cl_float>::value == true);
  static_assert(d::is_genfloatf<s::float4>::value == true);
  static_assert(d::is_genfloatf<s::float16>::value == true);
  static_assert(d::is_genfloatf<f_t>::value == true, "");

  static_assert(d::is_genfloatf<s::opencl::cl_int>::value == false);
  static_assert(d::is_genfloatf<i_t>::value == false, "");
  static_assert(d::is_genfloatf<t::c_t>::value == false, "");
  static_assert(d::is_genfloatf<t::d_t>::value == false, "");
  static_assert(d::is_genfloatf<v>::value == false, "");

  //

  static_assert(d::is_genfloat<s::opencl::cl_float>::value == true);
  static_assert(d::is_genfloat<s::vec<s::opencl::cl_float, 4>>::value == true);

  static_assert(d::is_ugenint<s::vec<s::opencl::cl_float, 4>>::value == false);
  static_assert(d::is_ugenint<s::float4>::value == false);

  static_assert(d::is_ugenint<s::opencl::cl_uint>::value == true);
  static_assert(d::is_ugenint<unsigned int>::value == true);

  static_assert(d::is_ugenint<s::vec<s::opencl::cl_uint, 3>>::value == true);
  static_assert(d::is_ugenint<s::uint3>::value == true);

  static_assert(d::is_half<s::half>::value);

  // TODO add checks for the following type traits
  /*
  is_doublen
  is_genfloatd

  is_halfn
  is_genfloath

  is_genfloat

  is_sgenfloat
  is_vgenfloat

  is_gengeofloat
  is_gengeodouble
  is_gengeohalf

  is_vgengeofloat
  is_vgengeodouble
  is_vgengeohalf

  is_gencrossfloat
  is_gencrossdouble
  is_gencrosshalf
  is_gencross

  is_charn
  is_scharn
  is_ucharn
  is_igenchar
  is_ugenchar
  is_genchar

  is_shortn
  is_genshort
  is_ushortn
  is_ugenshort

  is_uintn
  is_ugenint
  is_intn
  is_genint
  */

  /*
  is_ulonglongn
  is_ugenlonglong
  is_longlongn
  is_genlonglong

  is_igenlonginteger
  is_ugenlonginteger

  is_geninteger
  is_igeninteger
  is_ugeninteger
  is_sgeninteger
  is_vgeninteger


  is_sigeninteger
  is_sugeninteger
  is_vigeninteger
  is_vugeninteger

  is_gentype

  is_igeninteger8bit
  is_igeninteger16bit
  is_igeninteger32bit
  is_igeninteger64bit

  is_ugeninteger8bit
  is_ugeninteger16bit
  is_ugeninteger32bit
  is_ugeninteger64bit

  is_genintptr
  is_genfloatptr

  unsing_integeral_to_float_point
  */
  // is_nan_type
  static_assert(d::is_nan_type<unsigned long long int>::value == true, "");
  static_assert(d::is_nan_type<long long>::value == false, "");
  static_assert(d::is_nan_type<unsigned long long>::value == true, "");
  static_assert(d::is_nan_type<unsigned long>::value == true, "");
  static_assert(d::is_nan_type<long>::value == false, "");
  static_assert(d::is_nan_type<unsigned long>::value == true, "");
  /*
  float_point_to_sign_integeral

  make_unsigned
  make_larger
  */

  // checks for some type conversions.
  static_assert(std::is_same<d::SelectMatchingOpenCLType_t<s::opencl::cl_int>,
                             s::opencl::cl_int>::value);

  static_assert(
      std::is_same<d::SelectMatchingOpenCLType_t<s::vec<s::opencl::cl_int, 2>>,
                   s::vec<s::opencl::cl_int, 2>>::value);

  static_assert(std::is_same<
                d::SelectMatchingOpenCLType_t<s::multi_ptr<
                    s::opencl::cl_int, s::access::address_space::global_space,
                    s::access::decorated::yes>>,
                s::multi_ptr<s::opencl::cl_int,
                             s::access::address_space::global_space,
                             s::access::decorated::yes>>::value);

  static_assert(
      std::is_same<d::SelectMatchingOpenCLType_t<
                       s::multi_ptr<s::vec<s::opencl::cl_int, 2>,
                                    s::access::address_space::global_space,
                                    s::access::decorated::yes>>,
                   s::multi_ptr<s::vec<s::opencl::cl_int, 2>,
                                s::access::address_space::global_space,
                                s::access::decorated::yes>>::value);

  static_assert(std::is_same<d::SelectMatchingOpenCLType_t<long long>,
                             s::opencl::cl_long>::value);

  static_assert(
      std::is_same<d::SelectMatchingOpenCLType_t<s::vec<long long, 2>>,
                   s::vec<s::opencl::cl_long, 2>>::value);

  static_assert(
      std::is_same<d::SelectMatchingOpenCLType_t<s::multi_ptr<
                       long long, s::access::address_space::global_space,
                       s::access::decorated::yes>>,
                   s::multi_ptr<s::opencl::cl_long,
                                s::access::address_space::global_space,
                                s::access::decorated::yes>>::value);

  static_assert(
      std::is_same<
          d::SelectMatchingOpenCLType_t<s::multi_ptr<
              s::vec<long long, 2>, s::access::address_space::global_space,
              s::access::decorated::yes>>,
          s::multi_ptr<s::vec<s::opencl::cl_long, 2>,
                       s::access::address_space::global_space,
                       s::access::decorated::yes>>::value);

#ifdef __SYCL_DEVICE_ONLY__
  static_assert(
      std::is_same<d::ConvertToOpenCLType_t<s::vec<s::opencl::cl_int, 2>>,
                   s::vec<s::opencl::cl_int, 2>::vector_t>::value);
  static_assert(std::is_same<d::ConvertToOpenCLType_t<s::vec<long long, 2>>,
                             s::vec<s::opencl::cl_long, 2>::vector_t>::value);
  static_assert(std::is_same<
                d::ConvertToOpenCLType_t<s::multi_ptr<
                    s::opencl::cl_int, s::access::address_space::global_space,
                    s::access::decorated::yes>>,
                s::multi_ptr<s::opencl::cl_int,
                             s::access::address_space::global_space,
                             s::access::decorated::yes>::pointer>::value);
  static_assert(
      std::is_same<d::ConvertToOpenCLType_t<
                       s::multi_ptr<s::vec<s::opencl::cl_int, 4>,
                                    s::access::address_space::global_space,
                                    s::access::decorated::yes>>,
                   s::multi_ptr<s::vec<s::opencl::cl_int, 4>::vector_t,
                                s::access::address_space::global_space,
                                s::access::decorated::yes>::pointer>::value);
#endif
  static_assert(std::is_same<d::ConvertToOpenCLType_t<s::half>,
                             d::half_impl::BIsRepresentationT>::value,
                "");

  s::multi_ptr<int, s::access::address_space::global_space,
               s::access::decorated::yes>
      mp;
  int *dp = mp;
}
