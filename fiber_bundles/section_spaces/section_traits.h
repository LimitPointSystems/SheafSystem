
//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//   http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//

// Interface for class section_traits

#ifndef SECTION_TRAITS_H
#define SECTION_TRAITS_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef STD_STRING_H
#include "std_string.h"
#endif

namespace sheaf
{
class poset_path;
}

namespace fiber_bundle
{

using namespace sheaf;


///
/// Features describing a section type.
/// Declaration only; there is no generic implementation
/// for this template. It is implemented only via specializations.
///
template <typename sec_type>
struct section_traits;

class base_space_member;
class sec_at0;
class at0;

///
/// Features describing a sec_at0 as a section type.
///
template <>
struct SHEAF_DLL_SPEC section_traits<sec_at0>
{
  ///
  /// The standard fiber type.
  ///
  typedef at0 standard_fiber_type;

  ///
  /// The standard base type.
  ///
  typedef base_space_member standard_base_type;

  ///
  /// True if sec_type must use standard base type.
  ///
  static bool must_use_standard_base_type();

  ///
  /// The path of the standard fiber schema.
  ///
  static const poset_path& standard_fiber_schema_path();

  ///
  /// The path of the standard rep.
  ///
  static const poset_path& standard_rep_path();

  ///
  /// True if sec_type must use standard_rep_path.
  ///
  static bool must_use_standard_rep();

};

class sec_at1;
class at1;

///
/// Features describing a sec_at1 as a section type.
///
template <>
struct SHEAF_DLL_SPEC section_traits<sec_at1>
{
  ///
  /// The standard fiber type.
  ///
  typedef at1 standard_fiber_type;

  ///
  /// The standard base type.
  ///
  typedef base_space_member standard_base_type;

  ///
  /// True if sec_type must use standard base type.
  ///
  static bool must_use_standard_base_type();

  ///
  /// The path of the standard fiber schema.
  ///
  static const poset_path& standard_fiber_schema_path();

  ///
  /// The path of the standard rep.
  ///
  static const poset_path& standard_rep_path();

  ///
  /// True if sec_type must use standard_rep_path.
  ///
  static bool must_use_standard_rep();

};

class sec_at2_e2;
class at2_e2;

///
/// Features describing a sec_at2_e2 as a section type.
///
template <>
struct SHEAF_DLL_SPEC section_traits<sec_at2_e2>
{
  ///
  /// The standard fiber type.
  ///
  typedef at2_e2 standard_fiber_type;

  ///
  /// The standard base type.
  ///
  typedef base_space_member standard_base_type;

  ///
  /// True if sec_type must use standard base type.
  ///
  static bool must_use_standard_base_type();

  ///
  /// The path of the standard fiber schema.
  ///
  static const poset_path& standard_fiber_schema_path();

  ///
  /// The path of the standard rep.
  ///
  static const poset_path& standard_rep_path();

  ///
  /// True if sec_type must use standard_rep_path.
  ///
  static bool must_use_standard_rep();

};

class sec_at2_e3;
class at2_e3;

///
/// Features describing a sec_at2_e3 as a section type.
///
template <>
struct SHEAF_DLL_SPEC section_traits<sec_at2_e3>
{
  ///
  /// The standard fiber type.
  ///
  typedef at2_e3 standard_fiber_type;

  ///
  /// The standard base type.
  ///
  typedef base_space_member standard_base_type;

  ///
  /// True if sec_type must use standard base type.
  ///
  static bool must_use_standard_base_type();

  ///
  /// The path of the standard fiber schema.
  ///
  static const poset_path& standard_fiber_schema_path();

  ///
  /// The path of the standard rep.
  ///
  static const poset_path& standard_rep_path();

  ///
  /// True if sec_type must use standard_rep_path.
  ///
  static bool must_use_standard_rep();
};

class sec_at3_e3;
class at3_e3;

///
/// Features describing a sec_at3_e3 as a section type.
///
template <>
struct SHEAF_DLL_SPEC section_traits<sec_at3_e3>
{
  ///
  /// The standard fiber type.
  ///
  typedef at3_e3 standard_fiber_type;

  ///
  /// The standard base type.
  ///
  typedef base_space_member standard_base_type;

  ///
  /// True if sec_type must use standard base type.
  ///
  static bool must_use_standard_base_type();

  ///
  /// The path of the standard fiber schema.
  ///
  static const poset_path& standard_fiber_schema_path();

  ///
  /// The path of the standard rep.
  ///
  static const poset_path& standard_rep_path();

  ///
  /// True if sec_type must use standard_rep_path.
  ///
  static bool must_use_standard_rep();
};

class sec_e1;
class e1;

///
/// Features describing a sec_e1 as a section type.
///
template <>
struct SHEAF_DLL_SPEC section_traits<sec_e1>
{
  ///
  /// The standard fiber type.
  ///
  typedef e1 standard_fiber_type;

  ///
  /// The standard base type.
  ///
  typedef base_space_member standard_base_type;

  ///
  /// True if sec_type must use standard base type.
  ///
  static bool must_use_standard_base_type();

  ///
  /// The path of the standard fiber schema.
  ///
  static const poset_path& standard_fiber_schema_path();

  ///
  /// The path of the standard rep.
  ///
  static const poset_path& standard_rep_path();

  ///
  /// True if sec_type must use standard_rep_path.
  ///
  static bool must_use_standard_rep();
};

class sec_e1_uniform;
class e1;
class structured_block_1d;

///
/// Features describing a sec_e1_uniform as a section type.
///
template <>
struct SHEAF_DLL_SPEC section_traits<sec_e1_uniform>
{
  ///
  /// The standard fiber type.
  ///
  typedef e1 standard_fiber_type;

  ///
  /// The standard base type.
  ///
  typedef structured_block_1d standard_base_type;

  ///
  /// True if sec_type must use standard base type.
  ///
  static bool must_use_standard_base_type();

  ///
  /// The path of the standard fiber schema.
  ///
  static const poset_path& standard_fiber_schema_path();

  ///
  /// The path of the standard rep.
  ///
  static const poset_path& standard_rep_path();

  ///
  /// True if sec_type must use standard_rep_path.
  ///
  static bool must_use_standard_rep();
};

class sec_e2;
class e2;

///
/// Features describing a sec_e2 as a section type.
///
template <>
struct SHEAF_DLL_SPEC section_traits<sec_e2>
{
  ///
  /// The standard fiber type.
  ///
  typedef e2 standard_fiber_type;

  ///
  /// The standard base type.
  ///
  typedef base_space_member standard_base_type;

  ///
  /// True if sec_type must use standard base type.
  ///
  static bool must_use_standard_base_type();

  ///
  /// The path of the standard fiber schema.
  ///
  static const poset_path& standard_fiber_schema_path();

  ///
  /// The path of the standard rep.
  ///
  static const poset_path& standard_rep_path();

  ///
  /// True if sec_type must use standard_rep_path.
  ///
  static bool must_use_standard_rep();
};

class sec_e2_uniform;
class e2;
class structured_block_2d;

///
/// Features describing a sec_e2_uniform as a section type.
///
template <>
struct SHEAF_DLL_SPEC section_traits<sec_e2_uniform>
{
  ///
  /// The standard fiber type.
  ///
  typedef e2 standard_fiber_type;

  ///
  /// The standard base type.
  ///
  typedef structured_block_2d standard_base_type;

  ///
  /// True if sec_type must use standard base type.
  ///
  static bool must_use_standard_base_type();

  ///
  /// The path of the standard fiber schema.
  ///
  static const poset_path& standard_fiber_schema_path();

  ///
  /// The path of the standard rep.
  ///
  static const poset_path& standard_rep_path();

  ///
  /// True if sec_type must use standard_rep_path.
  ///
  static bool must_use_standard_rep();
};

class sec_e3;
class e3;

///
/// Features describing a sec_e3 as a section type.
///
template <>
struct SHEAF_DLL_SPEC section_traits<sec_e3>
{
  ///
  /// The standard fiber type.
  ///
  typedef e3 standard_fiber_type;

  ///
  /// The standard base type.
  ///
  typedef base_space_member standard_base_type;

  ///
  /// True if sec_type must use standard base type.
  ///
  static bool must_use_standard_base_type();

  ///
  /// The path of the standard fiber schema.
  ///
  static const poset_path& standard_fiber_schema_path();

  ///
  /// The path of the standard rep.
  ///
  static const poset_path& standard_rep_path();

  ///
  /// True if sec_type must use standard_rep_path.
  ///
  static bool must_use_standard_rep();
};

class sec_e3_uniform;
class e3;
class structured_block_3d;

///
/// Features describing a sec_e3_uniform as a section type.
///
template <>
struct SHEAF_DLL_SPEC section_traits<sec_e3_uniform>
{
  ///
  /// The standard fiber type.
  ///
  typedef e3 standard_fiber_type;

  ///
  /// The standard base type.
  ///
  typedef structured_block_3d standard_base_type;

  ///
  /// True if sec_type must use standard base type.
  ///
  static bool must_use_standard_base_type();

  ///
  /// The path of the standard fiber schema.
  ///
  static const poset_path& standard_fiber_schema_path();

  ///
  /// The path of the standard rep.
  ///
  static const poset_path& standard_rep_path();

  ///
  /// True if sec_type must use standard_rep_path.
  ///
  static bool must_use_standard_rep();
};

class sec_jcb_e13;
class jcb_e13;

///
/// Features describing a sec_sec_jcb_e13 as a section type.
///
template <>
struct SHEAF_DLL_SPEC section_traits<sec_jcb_e13>
{
  ///
  /// The standard fiber type.
  ///
  typedef jcb_e13 standard_fiber_type;

  ///
  /// The standard base type.
  ///
  typedef base_space_member standard_base_type;

  ///
  /// True if sec_type must use standard base type.
  ///
  static bool must_use_standard_base_type();

  ///
  /// The path of the standard fiber schema.
  ///
  static const poset_path& standard_fiber_schema_path();

  ///
  /// The path of the standard rep.
  ///
  static const poset_path& standard_rep_path();

  ///
  /// True if sec_type must use standard_rep_path.
  ///
  static bool must_use_standard_rep();
};

class sec_jcb_e23;
class jcb_e23;

///
/// Features describing a sec_jcb_e23 as a section type.
///
template <>
struct SHEAF_DLL_SPEC section_traits<sec_jcb_e23>
{
  ///
  /// The standard fiber type.
  ///
  typedef jcb_e23 standard_fiber_type;

  ///
  /// The standard base type.
  ///
  typedef base_space_member standard_base_type;

  ///
  /// True if sec_type must use standard base type.
  ///
  static bool must_use_standard_base_type();

  ///
  /// The path of the standard fiber schema.
  ///
  static const poset_path& standard_fiber_schema_path();

  ///
  /// The path of the standard rep.
  ///
  static const poset_path& standard_rep_path();

  ///
  /// True if sec_type must use standard_rep_path.
  ///
  static bool must_use_standard_rep();
};

class sec_jcb_e33;
class jcb_e33;

///
/// Features describing a sec_jcb_e33 as a section type.
///
template <>
struct SHEAF_DLL_SPEC section_traits<sec_jcb_e33>
{
  ///
  /// The standard fiber type.
  ///
  typedef jcb_e33 standard_fiber_type;

  ///
  /// The standard base type.
  ///
  typedef base_space_member standard_base_type;

  ///
  /// True if sec_type must use standard base type.
  ///
  static bool must_use_standard_base_type();

  ///
  /// The path of the standard fiber schema.
  ///
  static const poset_path& standard_fiber_schema_path();

  ///
  /// The path of the standard rep.
  ///
  static const poset_path& standard_rep_path();

  ///
  /// True if sec_type must use standard_rep_path.
  ///
  static bool must_use_standard_rep();
};


class sec_met_e1;
class met_e1;

///
/// Features describing a sec_met_e1 as a section type.
///
template <>
struct SHEAF_DLL_SPEC section_traits<sec_met_e1>
{
  ///
  /// The standard fiber type.
  ///
  typedef met_e1 standard_fiber_type;

  ///
  /// The standard base type.
  ///
  typedef base_space_member standard_base_type;

  ///
  /// True if sec_type must use standard base type.
  ///
  static bool must_use_standard_base_type();

  ///
  /// The path of the standard fiber schema.
  ///
  static const poset_path& standard_fiber_schema_path();

  ///
  /// The path of the standard rep.
  ///
  static const poset_path& standard_rep_path();

  ///
  /// True if sec_type must use standard_rep_path.
  ///
  static bool must_use_standard_rep();
};

class sec_met_e2;
class met_e2;

///
/// Features describing a sec_met_e2 as a section type.
///
template <>
struct SHEAF_DLL_SPEC section_traits<sec_met_e2>
{
  ///
  /// The standard fiber type.
  ///
  typedef met_e2 standard_fiber_type;

  ///
  /// The standard base type.
  ///
  typedef base_space_member standard_base_type;

  ///
  /// True if sec_type must use standard base type.
  ///
  static bool must_use_standard_base_type();

  ///
  /// The path of the standard fiber schema.
  ///
  static const poset_path& standard_fiber_schema_path();

  ///
  /// The path of the standard rep.
  ///
  static const poset_path& standard_rep_path();

  ///
  /// True if sec_type must use standard_rep_path.
  ///
  static bool must_use_standard_rep();
};

class sec_met_e3;
class met_e3;

///
/// Features describing a sec_met_e3 as a section type.
///
template <>
struct SHEAF_DLL_SPEC section_traits<sec_met_e3>
{
  ///
  /// The standard fiber type.
  ///
  typedef met_e3 standard_fiber_type;

  ///
  /// The standard base type.
  ///
  typedef base_space_member standard_base_type;

  ///
  /// True if sec_type must use standard base type.
  ///
  static bool must_use_standard_base_type();

  ///
  /// The path of the standard fiber schema.
  ///
  static const poset_path& standard_fiber_schema_path();

  ///
  /// The path of the standard rep.
  ///
  static const poset_path& standard_rep_path();

  ///
  /// True if sec_type must use standard_rep_path.
  ///
  static bool must_use_standard_rep();
};


class sec_st2_e2;
class st2_e2;

///
/// Features describing a sec_st2_e2 as a section type.
///
template <>
struct SHEAF_DLL_SPEC section_traits<sec_st2_e2>
{
  ///
  /// The standard fiber type.
  ///
  typedef st2_e2 standard_fiber_type;

  ///
  /// The standard base type.
  ///
  typedef base_space_member standard_base_type;

  ///
  /// True if sec_type must use standard base type.
  ///
  static bool must_use_standard_base_type();

  ///
  /// The path of the standard fiber schema.
  ///
  static const poset_path& standard_fiber_schema_path();

  ///
  /// The path of the standard rep.
  ///
  static const poset_path& standard_rep_path();

  ///
  /// True if sec_type must use standard_rep_path.
  ///
  static bool must_use_standard_rep();
};

class sec_st2_e3;
class st2_e3;

///
/// Features describing a sec_st2_e3 as a section type.
///
template <>
struct SHEAF_DLL_SPEC section_traits<sec_st2_e3>
{
  ///
  /// The standard fiber type.
  ///
  typedef st2_e3 standard_fiber_type;

  ///
  /// The standard base type.
  ///
  typedef base_space_member standard_base_type;

  ///
  /// True if sec_type must use standard base type.
  ///
  static bool must_use_standard_base_type();

  ///
  /// The path of the standard fiber schema.
  ///
  static const poset_path& standard_fiber_schema_path();

  ///
  /// The path of the standard rep.
  ///
  static const poset_path& standard_rep_path();

  ///
  /// True if sec_type must use standard_rep_path.
  ///
  static bool must_use_standard_rep();
};

class sec_st3_e3;
class st3_e3;

///
/// Features describing a sec_st3_e3 as a section type.
///
template <>
struct SHEAF_DLL_SPEC section_traits<sec_st3_e3>
{
  ///
  /// The standard fiber type.
  ///
  typedef st3_e3 standard_fiber_type;

  ///
  /// The standard base type.
  ///
  typedef base_space_member standard_base_type;

  ///
  /// True if sec_type must use standard base type.
  ///
  static bool must_use_standard_base_type();

  ///
  /// The path of the standard fiber schema.
  ///
  static const poset_path& standard_fiber_schema_path();

  ///
  /// The path of the standard rep.
  ///
  static const poset_path& standard_rep_path();

  ///
  /// True if sec_type must use standard_rep_path.
  ///
  static bool must_use_standard_rep();
};


class sec_st4_e2;
class st4_e2;

///
/// Features describing a sec_st4_e2 as a section type.
///
template <>
struct SHEAF_DLL_SPEC section_traits<sec_st4_e2>
{
  ///
  /// The standard fiber type.
  ///
  typedef st4_e2 standard_fiber_type;

  ///
  /// The standard base type.
  ///
  typedef base_space_member standard_base_type;

  ///
  /// True if sec_type must use standard base type.
  ///
  static bool must_use_standard_base_type();

  ///
  /// The path of the standard fiber schema.
  ///
  static const poset_path& standard_fiber_schema_path();

  ///
  /// The path of the standard rep.
  ///
  static const poset_path& standard_rep_path();

  ///
  /// True if sec_type must use standard_rep_path.
  ///
  static bool must_use_standard_rep();
};

class sec_st4_e3;
class st4_e3;

///
/// Features describing a sec_t3_e3 as a section type.
///
template <>
struct SHEAF_DLL_SPEC section_traits<sec_st4_e3>
{
  ///
  /// The standard fiber type.
  ///
  typedef st4_e3 standard_fiber_type;

  ///
  /// The standard base type.
  ///
  typedef base_space_member standard_base_type;

  ///
  /// True if sec_type must use standard base type.
  ///
  static bool must_use_standard_base_type();

  ///
  /// The path of the standard fiber schema.
  ///
  static const poset_path& standard_fiber_schema_path();

  ///
  /// The path of the standard rep.
  ///
  static const poset_path& standard_rep_path();

  ///
  /// True if sec_type must use standard_rep_path.
  ///
  static bool must_use_standard_rep();
};

class sec_t2_e2;
class t2_e2;

///
/// Features describing a sec_t2_e2 as a section type.
///
template <>
struct SHEAF_DLL_SPEC section_traits<sec_t2_e2>
{
  ///
  /// The standard fiber type.
  ///
  typedef t2_e2 standard_fiber_type;

  ///
  /// The standard base type.
  ///
  typedef base_space_member standard_base_type;

  ///
  /// True if sec_type must use standard base type.
  ///
  static bool must_use_standard_base_type();

  ///
  /// The path of the standard fiber schema.
  ///
  static const poset_path& standard_fiber_schema_path();

  ///
  /// The path of the standard rep.
  ///
  static const poset_path& standard_rep_path();

  ///
  /// True if sec_type must use standard_rep_path.
  ///
  static bool must_use_standard_rep();
};

class sec_t2_e3;
class t2_e3;

///
/// Features describing a sec_t2_e3 as a section type.
///
template <>
struct SHEAF_DLL_SPEC section_traits<sec_t2_e3>
{
  ///
  /// The standard fiber type.
  ///
  typedef t2_e3 standard_fiber_type;

  ///
  /// The standard base type.
  ///
  typedef base_space_member standard_base_type;

  ///
  /// True if sec_type must use standard base type.
  ///
  static bool must_use_standard_base_type();

  ///
  /// The path of the standard fiber schema.
  ///
  static const poset_path& standard_fiber_schema_path();

  ///
  /// The path of the standard rep.
  ///
  static const poset_path& standard_rep_path();

  ///
  /// True if sec_type must use standard_rep_path.
  ///
  static bool must_use_standard_rep();
};

class sec_t3_e3;
class t3_e3;

///
/// Features describing a sec_t3_e3 as a section type.
///
template <>
struct SHEAF_DLL_SPEC section_traits<sec_t3_e3>
{
  ///
  /// The standard fiber type.
  ///
  typedef t3_e3 standard_fiber_type;

  ///
  /// The standard base type.
  ///
  typedef base_space_member standard_base_type;

  ///
  /// True if sec_type must use standard base type.
  ///
  static bool must_use_standard_base_type();

  ///
  /// The path of the standard fiber schema.
  ///
  static const poset_path& standard_fiber_schema_path();

  ///
  /// The path of the standard rep.
  ///
  static const poset_path& standard_rep_path();

  ///
  /// True if sec_type must use standard_rep_path.
  ///
  static bool must_use_standard_rep();
};

class sec_t4_e2;
class t4_e2;

///
/// Features describing a sec_t4_e2 as a section type.
///
template <>
struct SHEAF_DLL_SPEC section_traits<sec_t4_e2>
{
  ///
  /// The standard fiber type.
  ///
  typedef t4_e2 standard_fiber_type;

  ///
  /// The standard base type.
  ///
  typedef base_space_member standard_base_type;

  ///
  /// True if sec_type must use standard base type.
  ///
  static bool must_use_standard_base_type();

  ///
  /// The path of the standard fiber schema.
  ///
  static const poset_path& standard_fiber_schema_path();

  ///
  /// The path of the standard rep.
  ///
  static const poset_path& standard_rep_path();

  ///
  /// True if sec_type must use standard_rep_path.
  ///
  static bool must_use_standard_rep();
};

class sec_t4_e3;
class t4_e3;

///
/// Features describing a sec_t3_e3 as a section type.
///
template <>
struct SHEAF_DLL_SPEC section_traits<sec_t4_e3>
{
  ///
  /// The standard fiber type.
  ///
  typedef t4_e3 standard_fiber_type;

  ///
  /// The standard base type.
  ///
  typedef base_space_member standard_base_type;

  ///
  /// True if sec_type must use standard base type.
  ///
  static bool must_use_standard_base_type();

  ///
  /// The path of the standard fiber schema.
  ///
  static const poset_path& standard_fiber_schema_path();

  ///
  /// The path of the standard rep.
  ///
  static const poset_path& standard_rep_path();

  ///
  /// True if sec_type must use standard_rep_path.
  ///
  static bool must_use_standard_rep();
};


class sec_vd;
class vd;

///
/// Features describing a sec_vd as a section type.
///
template <>
struct SHEAF_DLL_SPEC section_traits<sec_vd>
{
  ///
  /// The standard fiber type.
  ///
  typedef vd standard_fiber_type;

  ///
  /// The standard base type.
  ///
  typedef base_space_member standard_base_type;

  ///
  /// True if sec_type must use standard base type.
  ///
  static bool must_use_standard_base_type();

  ///
  /// The path of the standard fiber schema.
  ///
  static const poset_path& standard_fiber_schema_path();

  ///
  /// The path of the standard rep.
  ///
  static const poset_path& standard_rep_path();

  ///
  /// True if sec_type must use standard_rep_path.
  ///
  static bool must_use_standard_rep();
};

} // namespace fiber_bundle

#endif // ifndef SECTION_TRAITS_H
