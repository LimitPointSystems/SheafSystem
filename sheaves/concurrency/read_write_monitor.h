
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Interface for class READ_WRITE_MONITOR


#ifndef READ_WRITE_MONITOR_H
#define READ_WRITE_MONITOR_H

#ifndef SHEAF_DLL_SPEC_H
#include "sheaf_dll_spec.h"
#endif


#ifdef _PTHREADS

// hash map only used with threads
// hash_map.h includes hashtable.h includes stl_alloc.h includes time.h
// causes conflict in declaration of timespec in thread_condition_variable.h
// if hash_map.h included when not _PTHREADS
#ifndef STD_HASH_MAP_H
#include "std_hash_map.h"
#endif

#include "pthread.h"
#endif

#include "any.h"

#ifndef STD_UTILITY_H
#include "std_utility.h"
#endif

namespace sheaf
{
  
///
/// The monitor concurrency control interface.
/// Class READ_WRITE_MONITOR implements the monitor concurrency control
/// paradigm, as described in Andrews, "Concurrent Programming Principles
/// and Practice".  We have extended Andrews design to incorporate two
/// kinds of clients: threads and objects. The thread client interface
/// corresponds to Andrew's design and is intended to mediate access by
/// multiple clients, each of which is expected to gain appropriate access,
/// execute some piece of code and release access.  The object client
/// interface is intended for use when a client object depends on the
/// monitored object not changing during the lifetime of the client object.
/// The client gains read-only access to the monitored object and releases
/// the access only when it (the client) is deleted. The read access prevents
/// any thread from gaining write access and hence locks the monitored object
/// for the life of the client. The motivating application for the object
/// client interface is the need to lock poset objects which are being used
/// as the schema for some other (client) poset object. <br>
/// <br>
/// Note that the monitor protocol for the per-thread access control only works
/// if three conditions are satisfied: <br>
/// <br>
/// request_precedes_access: <br>
/// every client always requests access before accessing the object <br>
/// <br>
/// request_precedes_release: <br>
///  every release call by this thread is always preceded by a request
///      call by this thread <br>
/// <br>
/// release_follows_request: <br>
///  every request call by this thread is always followed by a release
///      call by this thread <br>
/// <br>
/// The latter two conditions require that request/release always occur in
/// matching pairs. <br>
/// <br>
/// We are currently enforcing request_precedes_access and
/// request_precedes_release via precondition assertions but we are not
/// enforcing release_follows_request because we don't see any way to do it.<br>
/// <br>
/// We sometimes refer to a client that satisfies request_precedes_access as a
/// "polite" client, and a client that satisfies request_precedes_release and
/// release_follows_request as a "proper" client. The read_write_monitor
/// protocol implemented here requires clients to be both polite and proper.
/// <br>
/// A note on constness. "Logically" const member functions (queries) of monitored
/// classes must be able to get and release read access. This implies that
/// get_read_access and release_access must be const; which in turn requires
/// that in this class most of the other member functions are const and all 
/// the data members are mutable.
///
class SHEAF_DLL_SPEC read_write_monitor : public any
{
  friend class read_write_monitor_handle;

public:
  // ===========================================================
  /// @name READ_WRITE_MONITOR FACET
  // ===========================================================
  //@{

public:
 
  // Constructors:

  ///
  /// Default Constructor
  ///
  read_write_monitor();

  ///
  /// Destructor
  ///
  virtual ~read_write_monitor();

protected:

private:

  //@}

  // ===========================================================
  /// @name GLOBAL ACCESS CONTROL FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if access control mechanism is disabled.
  /// Default value is enabled (false) and access is controlled
  /// by the per-thread access control functions.
  /// Disabled (true) is equivalent to having read-write access
  /// at all times, irrespective of any access control requests.
  ///
  static bool access_control_disabled();

  //   ///
  //   /// Disables access control.
  //   /// Disabled (true) is equivalent to having read-write access
  //   /// at all times, irrespective of any access control requests.
  //   /// Should only be invoked once at beginning of a program, before any
  //   /// other SheafSystem calls. Once disabled, access control can not be re-enabled.
  //   ///
  //   static void disable_access_control();

  ///
  /// Enables access control.
  /// Should only be invoked once at beginning of a program, before any
  /// other SheafSystem calls. Once enabled, access control can not be disabled.
  ///
  static void enable_access_control();

protected:

private:

  ///
  /// True if access control mechanism is disabled.
  ///
  static bool& private_access_control_disabled();  

  //@}
 
  // ===========================================================
  /// @name PER-THREAD ACCESS CONTROL FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if this thread has read-only or read-write access
  ///
  bool is_read_accessible() const;

  ///
  /// True if this thread has neither read-only or read-write access
  /// or if access control is disabled.
  ///
  bool is_not_read_accessible() const;

  ///
  /// True if this thread has read-write access or if access control is not enabled.
  ///
  bool is_read_write_accessible() const;

  ///
  /// True if this thread does not have read-write access or if access control is not enabled.
  ///
  bool is_not_read_write_accessible() const;

  ///
  /// True if this thread has read-only access.
  ///
  bool is_read_only_accessible() const;

  ///
  /// True if this thread does not have read-only access.
  ///
  bool is_not_read_only_accessible() const;

  ///
  /// Number of times access has been granted without a corresponding release.
  ///
  int access_request_depth() const;

  ///
  /// Get read access to the state associated with this.
  ///
  void get_read_access() const;

  ///
  /// Get read write access to the state associated with this.  If
  /// release_read_only_access is requested, read only access will be
  /// released then read_write_access will be requested, finally the
  /// same level of read_access as before will be requested.
  ///
  void get_read_write_access(bool xrelease_read_only_access = false);

  ///
  /// Release access. If xall is true, release all levels of access.
  /// Otherwise, release one level of access.
  ///
  void release_access(bool xall = false) const;

protected:

  ///
  /// True if access guards disabled.
  ///
  bool access_guards_disabled() const;

  ///
  /// Disables access gaurds; intended for use only within constructors of
  /// monitored objects, where no other client can possibly have access (yet).
  ///
  void disable_access_guards();

  ///
  /// Re-enables access guards.
  ///
  void enable_access_guards();

private:

  ///
  /// True if this thread has read-write access.
  ///
  bool uncontrolled_is_read_write_accessible() const;

  ///
  /// True if this thread has read-only access.
  ///
  bool uncontrolled_is_read_only_accessible() const;

  ///
  /// True if access guards disabled.
  ///
  bool _access_guards_disabled;

  ///
  /// Number of clients with read-only permission.
  ///
  mutable int _ro_ct;

  ///
  /// Number of clients with read-write permission.
  ///
  mutable int _rw_ct;

  // Strictly speaking, we don't need _ro_ct and _rw_ct in
  // the unthreaded case, but we use them anyway to make the
  // threaded and unthreaded implementations more similar.

  struct SHEAF_DLL_SPEC thread_state_t
  {
    ///
    /// The access mode;
    /// < 0 read-only access, == 0 no access, > 0 read-write access
    ///
    int  _access_mode;

    ///
    /// The access depth at which read_only acccess wwas switched
    /// to read-write access, if any.
    ///
    size_t _switch_depth;

    ///
    /// True if any client has had read-write access to this object
    /// since the last call to clear_is_modified();
    /// Set by release_read_write_access, cleared by client.
    ///
    bool _is_modified;
  };


#ifdef _PTHREADS

  ///
  /// Access state for each thread
  ///
  mutable hash_map<pthread_t, thread_state_t> _thread_state;

  ///
  /// Thread lock.
  ///
  mutable pthread_cond_t lock_free;

  ///
  /// Thread mutex.
  ///
  mutable pthread_mutex_t read_write_monitor_mutex;

#else

  ///
  /// Access state if only a single thread.
  ///
  mutable thread_state_t _thread_state;

#endif


  ///
  /// Initializes the state (access mode and is_modified condition) for this thread.
  ///
  void initialize_thread_state();

  ///
  /// True if a state has been allocated and initialized for this thread.
  ///
  bool contains_thread_state() const;

  ///
  /// The state (access mode, switch depth, and is_modified condition) of this thread.
  ///
  thread_state_t& thread_state() const;

  ///
  /// The access mode of this thread.
  ///
  int& access_mode() const;

  ///
  /// The switch depth of this thread.
  ///
  size_t& switch_depth() const;

  ///
  /// Monitor primitive; request for read only access.
  ///
  void request_read_only_access() const;

  ///
  /// Monitor primitive; request for read-write access.
  ///
  void request_read_write_access() const;

  ///
  /// Monitor primitive; release of read access.
  ///
  void release_read_only_access() const;

  ///
  /// Monitor primitive; release of read-write access.
  ///
  void release_read_write_access() const;

private:

  //@}

  // ===========================================================
  /// @name NOTIFICATION FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if any client has had read-write access to this object
  /// since the last call to clear_is_modified();
  ///
  bool is_modified() const;

  ///
  /// Makes is_modified() false
  ///
  void clear_is_modified();


protected:

private:

  //@}
 

  // ===========================================================
  /// @name MODE LOCK CONTROL FACET
  // ===========================================================
  //@{

public:

  ///
  /// @deprecated No replacement.
  /// "mode" is a submode of write access. The mode lock can be
  /// used by an application to prohibit access to some features
  /// even to a client that has write access. For instance, in
  /// class poset_state_handle, jim edit mode is disabled when
  /// is_mode_locked is true.
  ///
  bool  is_mode_locked() const;

  ///
  /// @deprecated No replacement.
  /// "mode" is a submode of write access. The mode lock can be
  /// used by an application to prohibit access to some features
  /// even to a client that has write access. For instance, in
  /// class poset_state_handle, jim edit mode is disabled when
  /// is_mode_locked is true.
  ///
  int   mode_lock_ct() const;

  ///
  /// @deprecated No replacement.
  /// "mode" is a submode of write access. The mode lock can be
  /// used by an application to prohibit access to some features
  /// even to a client that has write access. For instance, in
  /// class poset_state_handle, jim edit mode is disabled when
  /// is_mode_locked is true.
  ///
  void  get_mode_lock();

  ///
  /// @deprecated No replacement.
  /// "mode" is a submode of write access. The mode lock can be
  /// used by an application to prohibit access to some features
  /// even to a client that has write access. For instance, in
  /// class poset_state_handle, jim edit mode is disabled when
  /// is_mode_locked is true.
  ///
  void  release_mode_lock();

protected:

private:

  ///
  /// Number of clients with mode locks on this.
  ///
  int _mode_lock_ct;

  //@}
 

  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// True if other conforms to current
  ///
  virtual bool is_ancestor_of(const any* xother) const;


  ///
  /// Make a new instance of the same type as this
  ///
  virtual read_write_monitor* clone() const;


  ///
  /// Class invariant
  ///
  virtual bool invariant() const;

protected:

private:

  //@}
 

};

} // namespace sheaf

#endif // ifndef READ_WRITE_MONITOR_H
