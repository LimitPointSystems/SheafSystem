

//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class primitive_attributes

#ifndef PRIMITIVE_ATTRIBUTES_H
#define PRIMITIVE_ATTRIBUTES_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef PRIMITIVE_TYPE_H
#include "primitive_type.h"
#endif

namespace sheaf
{

template <typename T>
class block;
  
///
/// Abstract object wrapper for an instance of a primitive type.
///
class SHEAF_DLL_SPEC primitive_attributes
{
public:

  ///
  /// The prototype for the primitive value
  /// of the type associated with xid.
  ///
  static const primitive_attributes& prototype(pod_index_type xid);

  ///
  /// Type id of the primitive type with name or alias xname.
  ///
  static primitive_type id(const string& xname);

  ///
  /// Converts pod_index_type xid to primitive_type.
  ///
  static primitive_type id(pod_index_type xid)
  {
    return prototype(xid).id();
  };

  ///
  /// Size of the primitive type with id xid.
  ///
  static size_type size(pod_index_type xid)
  {
    return prototype(xid).size();
  };

  ///
  /// Alignment of the primitive type with id xid.
  ///
  static size_type alignment(pod_index_type xid)
  {
    return prototype(xid).alignment();
  };

  ///
  /// The name of primitive type with id xid.
  ///
  static const string& name(pod_index_type xid)
  {
    return prototype(xid).name();
  };

  ///
  /// Other names for the primitive type with id xid
  ///
  static const string& aliases(pod_index_type xid)
  {
    return prototype(xid).aliases();
  };

  ///
  /// The name in the hdf file of primitive type with id xid.
  ///
  static const string& hdf_type_name(pod_index_type xid)
  {
    return prototype(xid).hdf_type_name();
  };

  ///
  /// The hdf type of primitive type with id xid.
  ///
  static int hdf_type(pod_index_type xid)
  {
    return prototype(xid).hdf_type();
  };

  ///
  /// The default value for the primitive type associated with this.
  ///
  static primitive_buffer_type default_value(pod_index_type xid)
  {
    return prototype(xid).default_value();
  };

  ///
  /// Primitive descriptor for the primitive type with id xid.
  ///
  static primitive_descriptor descriptor(pod_index_type xid)
  {
    return prototype(xid); // Return invokes conversion function
  };

  // ===========================================================
  // CONSTRUCTORS
  // ===========================================================

  ///
  /// Default constructor.
  ///
  primitive_attributes();

  ///
  /// Copy constructor.
  ///
  primitive_attributes(const primitive_attributes& xother);

  ///
  /// Creates a new primitive value
  /// of the type associated with xid and default value.
  ///
  primitive_attributes(primitive_type xid);

  ///
  /// Conversion from pointer;
  /// creates a new primitive value of type VOID_STAR with value x.
  ///
  primitive_attributes(const void* x);

  ///
  /// Conversion from C string;
  /// creates a new primitive value of type C_STRING with value x.
  ///
  primitive_attributes(const char* x);

  ///
  /// Conversion from type T;
  /// creates a new primitive value of type T with value x.
  ///
  template <typename T>
  primitive_attributes(const T& x);

  ///
  /// Copy assignment operator.
  ///
  primitive_attributes& operator=(const primitive_attributes&);

  ///
  /// Destructor; not virtual, this can not be a base class.
  ///
  ~primitive_attributes();


  // ===========================================================
  // ATTRIBUTES
  // ===========================================================

  ///
  /// The id for the primitive type associated with this.
  ///
  primitive_type id() const
  {
    return _id;
  };

  ///
  /// The size of the primitive type associated with this.
  ///
  size_type size() const
  {
    return _size;
  };

  ///
  /// The alignment for the primitive type associated with this.
  ///
  size_type alignment() const
  {
    return _alignment;
  };

  ///
  /// The name of the primitive type associated with this.
  ///
  const string& name() const
  {
    return *_name;
  };

  ///
  /// Other names for the primitive type associated with this.
  ///
  const string& aliases() const
  {
    return *_aliases;
  };

  ///
  /// The name in the hdf file of the primitive type associated with this.
  ///
  const string& hdf_type_name() const
  {
    return *_hdf_type_name;
  };

  ///
  /// The hdf type of the primitive type associated with this.
  ///
  int hdf_type() const
  {
    return _hdf_type;
  };

  ///
  /// The default value for the primitive type associated with this.
  ///
  primitive_buffer_type default_value() const
  {
    return _default_value;
  };

  ///
  /// Conversion to primitive_descriptor
  ///
  operator primitive_descriptor() const;

private:

  ///
  /// The id for the primitive type associated with this.
  ///
  primitive_type _id;

  ///
  /// The size of the primitive type associated with this.
  ///
  size_type _size;

  ///
  /// The alignment for the primitive type associated with this.
  ///
  size_type _alignment;

  ///
  /// The name of the primitive type associated with this.
  ///
  const string* _name;

  ///
  /// Other names for the primitive type associated with this.
  ///
  const string* _aliases;

  ///
  /// The name in the hdf file of the primitive type associated with this.
  ///
  const string* _hdf_type_name;

  ///
  /// The hdf type used to represent the primitive type associated with this.
  ///
  int _hdf_type;

  ///
  /// The default value for the primitive type associated with this.
  ///
  primitive_buffer_type _default_value;

  ///
  /// Initializes prototypes for specific primitive types.
  ///
  static block<primitive_attributes>& make_prototypes();
};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
} // namespace sheaf

#endif // ifndef PRIMITIVE_ATTRIBUTES_H
