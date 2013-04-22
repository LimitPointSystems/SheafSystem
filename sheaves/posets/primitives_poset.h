

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @file
/// Interface for class primitives_poset.

#ifndef PRIMITIVES_POSET_H
#define PRIMITIVES_POSET_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef POSET_H
#include "poset.h"
#endif

#ifndef POSET_MEMBER_H
#include "total_poset_member.h"
#endif

#ifndef POSET_STATE_HANDLE_H
#include "poset_state_handle.h"
#endif

#ifndef STD_IOSTREAM_H
#include "std_iostream.h"
#endif

namespace sheaf
{

class namespace_poset;

///
/// The poset containing the primitive type definitions.
///
class SHEAF_DLL_SPEC primitives_poset : public poset_state_handle
{

  friend class namespace_poset;

  // ===========================================================
  /// @name PRIMITIVES_POSET FACET
  // ===========================================================
  //@{

public:

  ///
  /// The standard name for an instance of this class.
  ///
  static const string& standard_name();

  ///
  /// True if the primitive members are all attached.
  ///
  bool primitive_members_attached() const;

  ///
  /// Poset member representing primitive type bool (mutable version)
  ///
  inline abstract_poset_member& bool_type()
  {
    return _bool_type;
  };

  ///
  /// Poset member representing primitive type bool (const version)
  ///
  inline const abstract_poset_member& bool_type() const
  {
    return _bool_type;
  };

  ///
  /// Poset member representing primitive type char (mutable version)
  ///
  inline abstract_poset_member& char_type()
  {
    return _char_type;
  };

  ///
  /// Poset member representing primitive type char (const version)
  ///
  inline const abstract_poset_member& char_type() const
  {
    return _char_type;
  };

  ///
  /// Poset member representing primitive type signed char (mutable version)
  ///
  inline abstract_poset_member& signed_char_type()
  {
    return _signed_char_type;
  };

  ///
  /// Poset member representing primitive type signed char (const version)
  ///
  inline const abstract_poset_member& signed_char_type() const
  {
    return _signed_char_type;
  };

  ///
  /// Poset member representing primitive type short int (mutable version)
  ///
  inline abstract_poset_member& short_int_type()
  {
    return _short_int_type;
  };

  ///
  /// Poset member representing primitive type short int (const version)
  ///
  inline const abstract_poset_member& short_int_type() const
  {
    return _short_int_type;
  };

  ///
  /// Poset member representing primitive type int (mutable version)
  ///
  inline abstract_poset_member& int_type()
  {
    return _int_type;
  };

  ///
  /// Poset member representing primitive type int (const version)
  ///
  inline const abstract_poset_member& int_type() const
  {
    return _int_type;
  };

  ///
  /// Poset member representing primitive type int_type; alias for int (mutable version)
  ///
  inline abstract_poset_member& int_type_type()
  {
    return _int_type;
  };

  ///
  /// Poset member representing primitive type int_type; alias for int (const version)
  ///
  inline const abstract_poset_member& int_type_type() const
  {
    return _int_type;
  };

  ///
  /// Poset member representing primitive type pod_index_type; alias for int (mutable version)
  ///
  inline abstract_poset_member& pod_index_type_type()
  {
    return _int_type;
  };

  ///
  /// Poset member representing primitive type pod_index_type; alias for int (const version)
  ///
  inline const abstract_poset_member& pod_index_type_type() const
  {
    return _int_type;
  };

  ///
  /// Poset member representing primitive type long int (mutable version)
  ///
  inline abstract_poset_member& long_int_type()
  {
    return _long_int_type;
  };

  ///
  /// Poset member representing primitive type long int (const version)
  ///
  inline const abstract_poset_member& long_int_type() const
  {
    return _long_int_type;
  };

  ///
  /// Poset member representing primitive type long long int (mutable version)
  ///
  inline abstract_poset_member& long_long_int_type()
  {
    return _long_long_int_type;
  };

  ///
  /// Poset member representing primitive type long long int (const version)
  ///
  inline const abstract_poset_member& long_long_int_type() const
  {
    return _long_long_int_type;
  };

  ///
  /// Poset member representing primitive type unsigned char (mutable version)
  ///
  inline abstract_poset_member& unsigned_char_type()
  {
    return _unsigned_char_type;
  };

  ///
  /// Poset member representing primitive type unsigned char (const version)
  ///
  inline const abstract_poset_member& unsigned_char_type() const
  {
    return _unsigned_char_type;
  };

  ///
  /// Poset member representing primitive type unsigned short int (mutable version)
  ///
  inline abstract_poset_member& unsigned_short_int_type()
  {
    return _unsigned_short_int_type;
  };

  ///
  /// Poset member representing primitive type unsigned short int (const version)
  ///
  inline const abstract_poset_member& unsigned_short_int_type() const
  {
    return _unsigned_short_int_type;
  };

  ///
  /// Poset member representing primitive type unsigned int (mutable version)
  ///
  inline abstract_poset_member& unsigned_int_type()
  {
    return _unsigned_int_type;
  };

  ///
  /// Poset member representing primitive type unsigned int (const version)
  ///
  inline const abstract_poset_member& unsigned_int_type() const
  {
    return _unsigned_int_type;
  };

  ///
  /// Poset member representing primitive type unsigned long int (mutable version)
  ///
  inline abstract_poset_member& unsigned_long_int_type()
  {
    return _unsigned_long_int_type;
  };

  ///
  /// Poset member representing primitive type unsigned long int (const version)
  ///
  inline const abstract_poset_member& unsigned_long_int_type() const
  {
    return _unsigned_long_int_type;
  };

  ///
  /// Poset member representing primitive type unsigned long long int (mutable version)
  ///
  inline abstract_poset_member& unsigned_long_long_int_type()
  {
    return _unsigned_long_long_int_type;
  };

  ///
  /// Poset member representing primitive type unsigned long long int (const version)
  ///
  inline const abstract_poset_member& unsigned_long_long_int_type() const
  {
    return _unsigned_long_long_int_type;
  };

  ///
  /// Poset member representing primitive type float (mutable version)
  ///
  inline abstract_poset_member& float_type()
  {
    return _float_type;
  };

  ///
  /// Poset member representing primitive type float (const version)
  ///
  inline const abstract_poset_member& float_type() const
  {
    return _float_type;
  };

  ///
  /// Poset member representing primitive type double (mutable version)
  ///
  inline abstract_poset_member& double_type()
  {
    return _double_type;
  };

  ///
  /// Poset member representing primitive type double (const version)
  ///
  inline const abstract_poset_member& double_type() const
  {
    return _double_type;
  };

  ///
  /// Poset member representing primitive type long double (mutable version)
  ///
  inline abstract_poset_member& long_double_type()
  {
    return _long_double_type;
  };

  ///
  /// Poset member representing primitive type long double (const version)
  ///
  inline const abstract_poset_member& long_double_type() const
  {
    return _long_double_type;
  };

  ///
  /// Poset member representing primitive type void_star (mutable version)
  ///
  inline abstract_poset_member& void_star_type()
  {
    return _void_star_type;
  };

  ///
  /// Poset member representing primitive type void_star (const version)
  ///
  inline const abstract_poset_member& void_star_type() const
  {
    return _void_star_type;
  };

  ///
  /// Poset member representing primitive type c_string (mutable version)
  ///
  inline abstract_poset_member& c_string_type()
  {
    return _c_string_type;
  };

  ///
  /// Poset member representing primitive type c_string (const version)
  ///
  inline const abstract_poset_member& c_string_type() const
  {
    return _c_string_type;
  };

  ///
  /// Poset member representing primitive type namespace_relative_member_index (mutable version)
  ///
  inline abstract_poset_member& namespace_relative_member_index_type()
  {
    return _namespace_relative_member_index_type;
  };

  ///
  /// Poset member representing primitive type namespace_relative_member_index (const version)
  ///
  inline const abstract_poset_member& namespace_relative_member_index_type() const
  {
    return _namespace_relative_member_index_type;
  };

  ///
  /// Poset member representing primitive type namespace_relative_member_index (mutable version)
  ///
  inline abstract_poset_member& namespace_relative_subposet_index_type()
  {
    return _namespace_relative_subposet_index_type;
  };

  ///
  /// Poset member representing primitive type namespace_relative_member_index (const version)
  ///
  inline const abstract_poset_member& namespace_relative_subposet_index_type() const
  {
    return _namespace_relative_subposet_index_type;
  };

protected:

private:

  ///
  /// Poset member representing primitive type bool.
  ///
  total_poset_member _bool_type;

  ///
  /// Poset member representing primitive type char.
  ///
  total_poset_member _char_type;

  ///
  /// Poset member representing primitive type signed char.
  ///
  total_poset_member _signed_char_type;

  ///
  /// Poset member representing primitive type short int.
  ///
  total_poset_member _short_int_type;

  ///
  /// Poset member representing primitive type int.
  ///
  total_poset_member _int_type;

  ///
  /// Poset member representing primitive type long int.
  ///
  total_poset_member _long_int_type;

  ///
  /// Poset member representing primitive type long long int.
  ///
  total_poset_member _long_long_int_type;

  ///
  /// Poset member representing primitive type unsigned char.
  ///
  total_poset_member _unsigned_char_type;

  ///
  /// Poset member representing primitive type unsigned short int.
  ///
  total_poset_member _unsigned_short_int_type;

  ///
  /// Poset member representing primitive type unsigned int.
  ///
  total_poset_member _unsigned_int_type;

  ///
  /// Poset member representing primitive type unsigned long int.
  ///
  total_poset_member _unsigned_long_int_type;

  ///
  /// Poset member representing primitive type unsigned long long int.
  ///
  total_poset_member _unsigned_long_long_int_type;

  ///
  /// Poset member representing primitive type float.
  ///
  total_poset_member _float_type;

  ///
  /// Poset member representing primitive type double.
  ///
  total_poset_member _double_type;

  ///
  /// Poset member representing primitive type long double.
  ///
  total_poset_member _long_double_type;

  ///
  /// Poset member representing primitive type void_star.
  ///
  total_poset_member _void_star_type;

  ///
  /// Poset member representing primitive type c_string.
  ///
  total_poset_member _c_string_type;

  ///
  /// Poset member representing primitive type namespace_relative_member_index.
  ///
  total_poset_member _namespace_relative_member_index_type;

  ///
  /// Poset member representing primitive type namespace_relative_subposet_index.
  ///
  total_poset_member _namespace_relative_subposet_index_type;

  ///
  /// Creates an unattached handle
  ///
  primitives_poset();

  ///
  /// Destructor
  ///
  ~primitives_poset();

  ///
  /// Initializes primitive type member xmbr to type xtype.
  ///
  void initialize_primitive_member(total_poset_member& xmbr, primitive_type xtype);

  ///
  /// Handle for subposet which identifies table dofs.
  ///
  subposet* _table_dof_subposet;

  ///
  /// Handle for subposet which identifies row dofs.
  ///
  subposet* _row_dof_subposet;

  ///
  /// Creates prototype for this class and enters in factory.
  ///
  static bool make_prototype();

  //@}


  // ===========================================================
  /// @name POSET_STATE_HANDLE FACET
  // ===========================================================
  //@{

public:

  ///
  /// Identifier for the type of this poset.
  ///
  virtual poset_type type_id() const;

  ///
  /// The name of this class.
  ///
  virtual const char* class_name() const;

  ///
  /// True if xdof_map conforms to (i.e. is derived from) the type of
  /// row dof map required by this poset
  ///
  virtual bool row_dof_map_conforms(const poset_dof_map* xdof_map) const;

protected:

private:

  using poset_state_handle::attach_to_state;

  ///
  /// Attach this handle to the state with index xindex in host xhost
  ///
  virtual void attach_to_state(const namespace_poset* xhost, pod_index_type xindex);

  ///
  /// Detach this handle from its state
  ///
  virtual void detach_from_state();

  using poset_state_handle::new_state;

  ///
  /// Creates a new primitives poset in namespace xhost
  /// and attaches this handle to it.
  ///
  void new_state(const abstract_poset_member* xschema);

  ///
  /// Initializes the predefined members of the poset.
  ///
  virtual void initialize_standard_members();

  ///
  /// Creates the subposets common to every primitives poset.
  ///
  virtual void initialize_standard_subposets(const string& xname);

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Class invariant
  ///
  bool invariant() const;

protected:

private:

  ///
  /// Make a new instance of the same type as this
  ///
  virtual primitives_poset* clone() const;

  //@}
};

} // namespace sheaf

#endif // ifndef PRIMITIVES_POSET_H
