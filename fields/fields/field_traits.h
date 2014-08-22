
//
// Copyright (c) 2014 Limit Point Systems, Inc. 
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

// Interface for class field_traits.

#ifndef COM_LIMITPOINT_FIELDS_FIELD_TRAITS_H
#define COM_LIMITPOINT_FIELDS_FIELD_TRAITS_H

#ifndef COM_LIMITPOINT_SHEAF_SHEAF_DLL_SPEC_H
#include "ComLimitPoint/sheaf/sheaf_dll_spec.h"
#endif

namespace fiber_bundle
{
class sec_at0;
class sec_at1;
class sec_at2;
class sec_at2_e2;
class sec_at2_e3;
class sec_at3;
class sec_at3_e3;
class sec_atp;
class sec_e1;
class sec_e1_uniform;
class sec_e2;
class sec_e2_uniform;
class sec_e3;
class sec_e3_uniform;
class sec_e4;
class sec_ed;
class sec_jcb;
class sec_jcb_e13;
class sec_jcb_e23;
class sec_jcb_e33;
class sec_jcb_ed;
class sec_met;
class sec_met_e1;
class sec_met_e2;
class sec_met_e3;
class sec_met_ed;
class sec_st2;
class sec_st2_e2;
class sec_st2_e3;
class sec_st3;
class sec_st3_e3;
class sec_st4;
class sec_st4_e2;
class sec_st4_e3;
class sec_stp;
class sec_t2;
class sec_t2_e2;
class sec_t2_e3;
class sec_t3;
class sec_t3_e3;
class sec_t4;
class sec_t4_e2;
class sec_t4_e3;
class sec_tp;
}

namespace fields
{

using namespace fiber_bundle;

///
/// Features describing a field type.
/// Declaration only; there is no generic implementation
/// for this template. It is implemented only via specializations.
///
template <typename T>
class field_traits;

/// Forward declarations.

class field_at0;
class field_at1;
class field_at2;
class field_at2_e2;
class field_at2_e3;
class field_at3;
class field_at3_e3;
class field_atp;
class field_e1;
class field_e1_uniform;
class field_e2;
class field_e2_uniform;
class field_e3;
class field_e3_uniform;
class field_e4;
class field_ed;
class field_jcb;
class field_jcb_e13;
class field_jcb_e23;
class field_jcb_e33;
class field_jcb_ed;
class field_met;
class field_met_e1;
class field_met_e2;
class field_met_e3;
class field_met_ed;
class field_st2;
class field_st2_e2;
class field_st2_e3;
class field_st3;
class field_st3_e3;
class field_st4;
class field_st4_e2;
class field_st4_e3;
class field_stp;
class field_t2;
class field_t2_e2;
class field_t2_e3;
class field_t3;
class field_t3_e3;
class field_t4;
class field_t4_e2;
class field_t4_e3;
class field_tp;

template <>
class SHEAF_DLL_SPEC field_traits<sec_at0>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_at0 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_at1>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_at1 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_at2>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_at2 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_at2_e2>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_at2_e2 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_at2_e3>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_at2_e3 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_at3>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_at3 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_at3_e3>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_at3_e3 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_atp>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_atp field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_e1>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_e1 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_e1_uniform>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_e1_uniform field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_e2>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_e2 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_e2_uniform>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_e2_uniform field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_e3>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_e3 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_e3_uniform>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_e3_uniform field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_e4>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_e4 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_ed>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_ed field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_jcb>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_jcb field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_jcb_e13>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_jcb_e13 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_jcb_e23>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_jcb_e23 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_jcb_e33>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_jcb_e33 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_jcb_ed>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_jcb_ed field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_met>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_met field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_met_e1>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_met_e1 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_met_e2>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_met_e2 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_met_e3>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_met_e3 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_met_ed>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_met_ed field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_st2>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_st2 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_st2_e2>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_st2_e2 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_st2_e3>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_st2_e3 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_st3>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_st3 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_st3_e3>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_st3_e3 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_st4>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_st4 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_st4_e2>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_st4_e2 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_st4_e3>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_st4_e3 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_stp>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_stp field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_t2>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_t2 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_t2_e2>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_t2_e2 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_t2_e3>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_t2_e3 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_t3>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_t3 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_t3_e3>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_t3_e3 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_t4>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_t4 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_t4_e2>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_t4_e2 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_t4_e3>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_t4_e3 field_type;
};

template <>
class SHEAF_DLL_SPEC field_traits<sec_tp>
{
public:
  ///
  /// The type of the field.
  ///
  typedef field_tp field_type;
};


} // namespace fields

#endif // ifndef COM_LIMITPOINT_FIELDS_FIELD_TRAITS_H

