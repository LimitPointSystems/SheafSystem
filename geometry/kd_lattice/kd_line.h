

//
// Copyright (c) 2008 Limit Point Systems, Inc. 
//

/// @file
/// Interface for class kd_line

#ifndef KD_LINE_H
#define KD_LINE_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif

#ifndef KD_MEMBER_H
#include "kd_member.h"
#endif
 

namespace fiber_bundle
{
  class e3_lite;
}
  
namespace geometry
{
 
  class kd_lattice;
  
///
/// Planar polyline in the contents part of a kd_lattice.
///
class SHEAF_DLL_SPEC kd_line : public kd_member
{

  // ===========================================================
  /// @name KD_LINE FACET
  // ===========================================================
  //@{

public:
  
//   ///
//   /// Static const ints; hack to make MSC++ happy.
//   ///
//  enum static_const_int{};

  ///
  /// The name of the base space member prototype for lines.
  ///
  static const string& prototype_name();

  ///
  /// Creates a new line in xhost with the segments in xline_mbrs.
  ///
  kd_line(kd_lattice& xhost, const id_list& xline_mbrs);
  
  ///
  /// Creates a new line in xhost with the segments in xline_mbrs.
  ///
  static void new_line(kd_lattice& xhost, const id_list& xline_mbrs, scoped_index& xresult);
  
  ///
  /// Creates an instance attached to the line with id xid in xhost.
  ///
  kd_line(kd_lattice& xhost, const scoped_index& xid);

  ///
  /// Copy constructor
  ///
  kd_line(const kd_line& xother);

  ///
  /// Destructor
  ///
  virtual ~kd_line();

  ///
  /// The members of this line;
  /// if xinclude_segments, xmbrs includes segment ids, otherwise
  /// the result contains only points.
  ///
  void members(id_list_list& xmbrs, bool xinclude_segments) const;

  ///
  /// The members of the line with id xid in kd_lattice xhost;
  /// if xinclude_segments, xmbrs includes segment ids, otherwise
  /// the result contains only points.
  ///
  static void members(const kd_lattice& xhost, const scoped_index& xid, id_list_list& xmbrs, bool xinclude_segments);

  ///
  /// The members of this line and their coordinates;
  /// if xinclude_segments, xmbrs includes segment ids, otherwise
  /// the result contains only points.
  ///
  void members(id_list_list& xmbrs, pt_list_list& xcoords, bool xinclude_segments) const;

  ///
  /// The members of the line with id xid in kd_lattice xhost and their coordinates;
  /// if xinclude_segments, xmbrs includes segment ids, otherwise
  /// the result contains only points.
  ///
  static void members(const kd_lattice& xhost, const scoped_index& xid, id_list_list& xmbrs, pt_list_list& xcoords, bool xinclude_segments);

  ///
  /// The first member (a point) of this line..
  ///
  scoped_index front() const;
  
  ///
  /// The first member (a point) of the line with id xid in kd_lattice xhost.
  ///
  static scoped_index front(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// Extends this line by inserting a segment with first point xpt_id
  /// before the first segment. 
  ///
  void push_front(const scoped_index& xpt_id);

  ///
  /// Extends this line by inserting a segment with first point xpt_id
  /// before the first segment.
  ///
  static void push_front(kd_lattice& xhost, const scoped_index& xid, const scoped_index& xpt_id);

  ///
  /// The last member (a point) of this line..
  ///
  scoped_index back() const;
  
  ///
  /// The last member (a point) of the line with id xid in kd_lattice xhost.
  ///
  static scoped_index back(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// Extends this line by inserting a segment with second point xpt_id
  /// after the last segment.
  ///
  void push_back(const scoped_index& xpt_id);

  ///
  /// Extends this line by inserting a segment with second point xpt_id
  /// after the last segment.
  ///
  static void push_back(kd_lattice& xhost, const scoped_index& xid, const scoped_index& xpt_id);
  
  ///
  /// True if this line has no contents (line segments).
  ///
  bool is_empty() const;
  
  ///
  /// True if the line with id xid in kd_lattice xhost has no contents (line segments).
  ///
  static bool is_empty(const kd_lattice& xhost, const scoped_index& xid);
  
  ///
  /// True if the last point of this line is the same as the first.
  ///
  bool is_closed() const;
  
  ///
  /// True if the last point of the line with id xid in kd_lattice xhost is the same as the first.
  ///
  static bool is_closed(const kd_lattice& xhost, const scoped_index& xid);
  
  ///
  /// Inserts the segment with id xnew_seg_id in this line 
  /// before (xbefore true) or after (xbefore false) the 
  /// segment with id xold_seg_id.
  ///
  void insert_segment(const scoped_index& xnew_seg_id, const scoped_index& xold_seg_id, bool xbefore);
  
  ///
  /// Inserts the segment with id xnew_seg_id in the line 
  /// with id xid in kd_lattice xhost
  /// before (xafter false) or after (xafter true) the 
  /// segment with id xold_seg_id.
  ///
  static void insert_segment(kd_lattice& xhost, 
                             const scoped_index& xid, 
                             const scoped_index& xnew_seg_id, 
                             const scoped_index& xold_seg_id, 
                             bool xafter);

  ///
  /// The unique surface in which this line is directly contained..
  ///
  void surface(scoped_index& xresult) const;

  ///
  /// The unique surface in which the line with id xid in 
  /// kd_lattice xhost is directly contained..
  ///
  static void surface(const kd_lattice& xhost, const scoped_index& xid, scoped_index& xresult);

  ///
  /// The unique surface in which this line is directly contained..
  ///
  scoped_index surface() const;

  ///
  /// The unique surface in which the line with id xid in 
  /// kd_lattice xhost is directly contained..
  ///
  static scoped_index surface(const kd_lattice& xhost, const scoped_index& xid);

  ///
  /// The surfaces to which this line is directly or indirectly connected;
  /// intended for use after line insertion.
  ///
  void surfaces(id_set& xresult) const;

  ///
  /// The surfaces to which the line with id xid in kd_lattice xhost 
  /// is directly or indirectly connected; intended for use
  /// after line insertion.
  ///
  static void surfaces(const kd_lattice& xhost, const scoped_index& xid, id_set& xresult);

  ///
  /// The lines which this line is connected to by an intersection point,
  /// which may also be a truncation point. Intended for use after line removal.
  ///
  void connected_lines(id_set& xresult) const;

  ///
  /// The lines which the line with id xid in kd_lattice xhost 
  /// is connected to by an intersection point, which may also
  /// be a truncation point. Intended for use after line removal.
  ///
  static void connected_lines(const kd_lattice& xhost, const scoped_index& xid, id_set& xresult);

  ///
  /// The faces containung the segents in this line.
  ///
  void faces(id_list& xresult) const;

  ///
  /// The faces containing the segments in the line with id xid in kd_lattice xhost.
  ///
  static void faces(const kd_lattice& xhost, const scoped_index& xid, id_list& xresult);

  ///
  /// The zones containung the segents in this line.
  ///
  void zones(id_list& xresult) const;

  ///
  /// The zones containing the segments in the line with id xid in kd_lattice xhost.
  ///
  static void zones(const kd_lattice& xhost, const scoped_index& xid, id_list& xresult);

  ///
  /// The faces and zones containung the segents in this line.
  ///
  void cells(id_list& xfaces, id_list& xzones) const;

  ///
  /// The faces and zones containing the segments in the line with id xid in kd_lattice xhost.
  ///
  static void cells(const kd_lattice& xhost, const scoped_index& xid, id_list& xfaces, id_list& xzones);

  ///
  /// Clears the upper and lower cover of this line;
  /// returns the ids of the deactivated segments in xdeleted.
  ///
  void clear(pod_id_hash_set& xdeleted);  

  ///
  /// Clears the upper and lower cover of the line with id xid in kd_lattice xhost;
  /// returns the ids of the deactivated segments in xdeleted.
  ///
  static void clear(kd_lattice& xhost, const scoped_index& xid, pod_id_hash_set& xdeleted);  
  
  ///
  /// Deactivates this line.
  ///
  void deactivate();
  
  ///
  /// Deactivates the line with id xid in kd_lattice xhost.
  ///
  static void deactivate(kd_lattice& xhost, const scoped_index& xid);
  
  

protected:

  ///
  /// Default constructor; disabled.
  ///
  kd_line();

private:

  //@}

  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any *other) const;

  ///
  /// Virtual constructor, makes a new 
  /// instance of the same type as this
  ///
  virtual kd_line* clone() const;

  using kd_member::operator=;

  ///
  /// Assignment operator
  ///
  kd_line& operator=(const kd_line& xother);

  ///
  /// Assignment operator
  ///
  virtual kd_line& operator=(const any& xother);

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================
 
///
/// Insert kd_line& xn into ostream& xos.
///
SHEAF_DLL_SPEC 
ostream & operator << (ostream &xos, const kd_line& xn);

///
/// The deep size of kd_line& xn.
///
SHEAF_DLL_SPEC 
size_t deep_size(const kd_line& xn, bool xinclude_shallow = true);
  
} // end namespace geometry

#endif // ifndef KD_LINE_H
