

//
// Copyright (c) 2013 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class zone_partition

#ifndef ZONE_PARTITION_H
#define ZONE_PARTITION_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef ANY_H
#include "any.h"
#endif

#ifndef BLOCK_H
#include "block.h"
#endif

#ifndef COVER_SET_ITERATOR_H
#include "cover_set_iterator.h"
#endif
 
namespace fiber_bundle
{
  using namespace sheaf;
  
///
/// A description of a partition of the zones in a block.
///
/// @deprecated Removed from the build but remain around as a
///             reference for future development.
///
class SHEAF_DLL_SPEC zone_partition : public any
{

  // ===========================================================
  /// @name ZONE_PARTITION FACET
  // ===========================================================
  //@{

public:

  ///
  /// Creates an instance with name() xname and ct() xct.
  ///
  zone_partition(const string& xname, size_type xct);

  ///
  /// Destructor
  ///
  virtual ~zone_partition();

  ///
  /// The name of this partition.
  ///
  const string& name() const;

  ///
  /// The number of parts.
  ///
  size_type ct() const;

  ///
  /// The name of the xi-th part, if any.
  ///
  const string& part_name(size_type xi) const;

  ///
  /// Sets the name of the xi-th part to xname.
  ///
  void put_part_name(size_type xi, const string& xname);

  ///
  /// Sets the names of all the parts to xprefix + "_" + string(part number).
  ///
  void put_part_names(const string& xprefix);

  ///
  /// True if and only if every part has a non-empty name.
  ///
  bool all_parts_named() const;

  ///
  /// True if the partition has a zone id space for each part.
  ///
  bool has_zone_id_spaces() const;

  ///
  /// Sets has_zone_id_spaces() = xvalue.
  ///
  void put_has_zone_id_spaces(bool xvalue);

  ///
  /// The zones in the xi-th part.
  ///
  virtual cover_set_iterator part_zones(size_type xi) const = 0;

protected:

  ///
  /// The name of this partition.
  ///
  string _name;

  ///
  /// The number of partitions.
  ///
  size_type _ct;

  ///
  /// The names of the partitions.
  ///
  block<string> _part_names;

  ///
  /// True if the partition has a zone id space for each part.
  ///
  bool _has_zone_id_spaces;

  ///
  /// Default constructor; disabled.
  ///
  zone_partition();

private:

  ///
  /// Copy constructor; disabled.
  ///
  zone_partition(const zone_partition& xother);

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any* other) const;

  ///
  /// Virtual constructor, makes a new 
  /// instance of the same type as this
  ///
  virtual zone_partition* clone() const = 0;

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  //@}

private:


  ///
  /// Assignment operator; disabled.
  ///
  zone_partition& operator=(const zone_partition& xother);
  


};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
  
} // end namespace fiber_bundle

#endif // ifndef ZONE_PARTITION_H
