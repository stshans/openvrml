// -*- Mode: C++; indent-tabs-mode: nil; c-basic-offset: 4; fill-column: 78 -*-
//
// OpenVRML
//
// Copyright 2005, 2006, 2007, 2010  Braden McDaniel
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 3 of the License, or (at your
// option) any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, see <http://www.gnu.org/licenses/>.
//

# include "node_impl_util.h"

/**
 * @file openvrml/node_impl_util.h
 *
 * @brief Definition of utility classes to facilitate node implementations.
 */

/**
 * @def OPENVRML_NODE_INTERFACE_TUPLE_ELEM(index, tuple)
 *
 * @internal
 *
 * @hideinitializer
 *
 * @brief Get an element of a node interface tuple.
 *
 * @param index an index value from 0&ndash;3.
 * @param tuple a node interface
 *              <a href="http://www.boost.org/doc/libs/release/libs/preprocessor/doc/data/tuples.html">tuple</a>
 *              as described for use with
 *              @c #OPENVRML_NODE_IMPL_UTIL_DEFINE_DO_CREATE_TYPE.
 */

/**
 * @def OPENVRML_DEFINE_NODE_INTERFACE(interface_tuple)
 *
 * @internal
 *
 * @hideinitializer
 *
 * @brief Create an @c openvrml::node_interface from an interface tuple.
 *
 * @param interface_tuple   a node interface
 *                          <a href="http://www.boost.org/doc/libs/release/libs/preprocessor/doc/data/tuples.html">tuple</a>
 *                          as described for use with
 *                          @c #OPENVRML_NODE_IMPL_UTIL_DEFINE_DO_CREATE_TYPE.
 */

/**
 * @def OPENVRML_DEFINE_SUPPORTED_INTERFACES_ELEM(r, data, i, elem)
 *
 * @internal
 *
 * @hideinitializer
 *
 * @brief A helper macro used with
 *        @c <a href="http://www.boost.org/doc/libs/release/libs/preprocessor/doc/ref/seq_for_each_i.html">
 *        BOOST_PP_SEQ_FOR_EACH_I</a>.
 *
 * @param r     not used.
 * @param data  not used.
 * @param i     the index of the current repetition.
 * @param elem  a node interface
 *              <a href="http://www.boost.org/doc/libs/release/libs/preprocessor/doc/data/tuples.html">tuple</a>
 *              as described for use with
 *              @c #OPENVRML_NODE_IMPL_UTIL_DEFINE_DO_CREATE_TYPE.
 */

/**
 * @def OPENVRML_SUPPORTED_INTERFACES_TYPE(interface_seq)
 *
 * @internal
 *
 * @hideinitializer
 *
 * @brief The type of an array of supported @c openvrml::node_interface%s for
 *        a @c openvrml::node_metatype.
 *
 * This is a helper macro used in the implementation of
 * @c #OPENVRML_NODE_IMPL_UTIL_DEFINE_DO_CREATE_TYPE.
 *
 * @param interface_seq a <a href="http://www.boost.org/doc/libs/release/libs/preprocessor/doc/data/sequences.html">
 *                      Boost.Preprocessor sequence</a> of
 *                      <a href="http://www.boost.org/doc/libs/release/libs/preprocessor/doc/data/tuples.html">tuples</a>,
 *                      as provided to
 *                      @c #OPENVRML_NODE_IMPL_UTIL_DEFINE_DO_CREATE_TYPE.
 */

/**
 * @def OPENVRML_ADD_INTERFACE(node_type_obj, interface_type, supported_interface, node, handler)
 *
 * @internal
 *
 * @hideinitializer
 *
 * @brief A helper macro used to implement @c #OPENVRML_ADD_INTERFACE_TUPLE.
 *
 * @param node_type_obj         a concrete @c openvrml::node_type instance.
 * @param interface_type        a node interface type name, in all lower-case, as
 *                              described for use in the interface tuple
 *                              provided to
 *                              @c #OPENVRML_NODE_IMPL_UTIL_DEFINE_DO_CREATE_TYPE.
 * @param supported_interface   a @c openvrml::node_interface.
 * @param node                  a @c openvrml::node instance type.
 * @param handler               the name of a @p node member function that
 *                              implements the node interface.
 */

/**
 * @def OPENVRML_ADD_INTERFACE_TUPLE(node_type_obj, node_instance_type, node_interface, interface_tuple)
 *
 * @internal
 *
 * @hideinitializer
 *
 * @brief A helper macro used to implement
 *        @c #OPENVRML_ADD_INTERFACE_ALTERNATIVE.
 *
 * @param node_type_obj         a concrete @c openvrml::node_type instance.
 * @param node_instance_type    a concrete @c openvrml::node instance type.
 * @param node_interface        a @c openvrml::node_interface.
 * @param interface_tuple       a node interface
 *                              <a href="http://www.boost.org/doc/libs/release/libs/preprocessor/doc/data/tuples.html">tuple</a>
 *                              as described for use with
 *                              @c #OPENVRML_NODE_IMPL_UTIL_DEFINE_DO_CREATE_TYPE.
 */

/**
 * @def OPENVRML_ADD_INTERFACE_ALTERNATIVE(r, data, elem)
 *
 * @internal
 *
 * @hideinitializer
 *
 * @brief A helper macro used with
 *        @c <a href="http://www.boost.org/doc/libs/release/libs/preprocessor/doc/ref/seq_for_each.html">
 *        BOOST_PP_SEQ_FOR_EACH</a>.
 *
 * @param r     not used.
 * @param data  a <a href="http://www.boost.org/doc/libs/release/libs/preprocessor/doc/data/tuples.html">Boost.Preprocessor tuple</a> consisting of
 *              variable names for:
 *              -# the @c openvrml::node_interface that is the subject of the
 *                 current iteration;
 *              -# an iterator for the set of supported interfaces;
 *              -# the concrete @c openvrml::node_type instance;
 *              -# the concrete @c node type.
 * @param elem  
 *
 * This macro is used in the implementation of
 * @c #OPENVRML_NODE_IMPL_UTIL_DEFINE_DO_CREATE_TYPE.
 */

/**
 * @def OPENVRML_NODE_IMPL_UTIL_DEFINE_DO_CREATE_TYPE(namespace_scope, node_metatype_type, node_instance_type, interface_seq)
 *
 * @hideinitializer
 *
 * @brief Implement @c openvrml::node_metatype::do_create_type.
 *
 * Most significantly, @c OPENVRML_NODE_IMPL_UTIL_DEFINE_DO_CREATE_TYPE
 * generates a concrete @c openvrml::node_type implementation; by using this
 * macro to implement @c openvrml::node_metatype::do_create_type, one can
 * avoid manually creating a concrete @c openvrml::node_type.
 *
 * @c OPENVRML_NODE_IMPL_UTIL_DEFINE_DO_CREATE_TYPE is instantiated using a
 * <a href="http://www.boost.org/doc/libs/release/libs/preprocessor/doc/index.html">
 * Boost.Preprocessor</a> <a href="http://www.boost.org/doc/libs/release/libs/preprocessor/doc/data/sequences.html">sequence</a> of
 * <a href="http://www.boost.org/doc/libs/release/libs/preprocessor/doc/data/tuples.html">
 * tuples</a>.  @p interface_seq consists of tuples of the following form:
 *
 * <pre>
 * (@e interface-type, @e value-type, @e interface-id, @e handler)
 * </pre>
 *
 * @e interface-type and @e value-type are both all lower-case; @e
 * interface-id is a string literal; and @e handler is the identifier of the
 * member of @p node_instance_type that implements the interface.  For
 * example:
 *
 * @code
 * # define MY_NODE_INTERFACE_SEQ                                   \
 *    ((eventin,      sfbool,  "set_wiggly",  set_wiggly_listener)) \
 *    ((field,        sfbool,  "wiggly",      wiggly))              \
 *    ((exposedfield, mffloat, "heightField", height_field))
 * @endcode
 *
 * @c MY_NODE_INTERFACE_SEQ is then used to instantiate
 * @c OPENVRML_NODE_IMPL_UTIL_DEFINE_DO_CREATE_TYPE:
 *
 * @code
 * OPENVRML_NODE_IMPL_UTIL_DEFINE_DO_CREATE_TYPE(my_namespace,
 *                                               my_node_metatype,
 *                                               my_node,
 *                                               MY_NODE_INTERFACE_SEQ)
 * @endcode
 *
 * In this example, @c set_wiggly_listener, @c wiggly, and @c height_field are
 * all members of the @c my_node class.  @c set_wiggly_listener is an instance
 * of a class that inherits
 * @c openvrml::node_field_value_listener@<openvrml::sfbool>; @c wiggly is an
 * instance of @c openvrml::sfbool; and @c height_field is an instance of
 * @c openvrml::exposedfield@<openvrml::mffloat>.
 *
 * @param namespace_scope       the namespace scope where @p node_instance_type
 *                              is defined.
 * @param node_metatype_type    the name of the concrete
 *                              @c openvrml::node_metatype type for the node
 *                              implementation.
 * @param node_instance_type    the name of the concrete @c openvrml::node type
 *                              for the node implementation.
 * @param interface_seq         a <a href="http://www.boost.org/doc/libs/release/libs/preprocessor/doc/data/sequences.html">
 *                              Boost.Preprocessor sequence</a> of
 *                              <a href="http://www.boost.org/doc/libs/release/libs/preprocessor/doc/data/tuples.html">tuples</a>
 *                              defining the supported interfaces for the node
 *                              implementation and the @p node_instance_type
 *                              member that implements them.
 *
 * @sa openvrml::node_metatype::do_create_type
 */

/**
 * @namespace openvrml::node_impl_util
 *
 * @brief Utility classes to facilitate node implementations.
 *
 * While the API comprising the members of the @c openvrml namespace
 * provides everything @e necessary to implement nodes, node
 * implementation can be very verbose.  The members of the
 * @c openvrml::node_impl_util namespace can make node implementation
 * more concise by abstracting and providing code that many node
 * implementations are likely to have in common.
 *
 * In particular, @c node_type_impl centralizes the logic for generalized
 * field access. By using an instance of this class template for your @c
 * openvrml::node_type implementation you can avoid a lot of tedious and
 * repetitive code to implement @c openvrml::node::do_field,
 * @c openvrml::node::do_event_listener, and
 * @c openvrml::node::do_event_emitter.  Most %node implementations can take
 * advantage of this simply by using the
 * @c #OPENVRML_NODE_IMPL_UTIL_DEFINE_DO_CREATE_TYPE macro when implementing a
 * concrete @c openvrml::node_metatype.
 */

/**
 * @class openvrml::node_impl_util::ptr_to_polymorphic_mem openvrml/node_impl_util.h
 *
 * @brief Abstract base class for a pointer-to-polymorphic-member type.
 *
 * In conjunction with @c ptr_to_polymorphic_mem_impl, this class
 * circumvents the &ldquo;contravariance problem&rdquo; with pointer-to-member
 * types. That is, the type <code>Base Object::*</code> is not compatible with
 * the type <code>Derived Object::*</code>.
 *
 * @tparam MemberBase   the base type of the member.
 * @tparam Object       the type that contains the member.
 *
 * @sa openvrml::node_impl_util::ptr_to_polymorphic_mem_impl
 */

/**
 * @fn openvrml::node_impl_util::ptr_to_polymorphic_mem<MemberBase, Object>::~ptr_to_polymorphic_mem()
 *
 * @brief Destroy.
 *
 * @tparam MemberBase   the base type of the member.
 * @tparam Object       the type that contains the member.
 */

/**
 * @fn MemberBase & openvrml::node_impl_util::ptr_to_polymorphic_mem::deref(Object & obj)
 *
 * @brief Dereference.
 *
 * @tparam MemberBase   the base type of the member.
 * @tparam Object       the type that contains the member.
 *
 * @return a reference to the base type of the member.
 */

/**
 * @overload const MemberBase & openvrml::node_impl_util::ptr_to_polymorphic_mem::deref(const Object & obj)
 *
 * @tparam MemberBase   the base type of the member.
 * @tparam Object       the type that contains the member.
 *
 * @return a @c const reference to the base type of the member.
 */


/**
 * @class openvrml::node_impl_util::ptr_to_polymorphic_mem_impl openvrml/node_impl_util.h
 *
 * @brief Concrete pointer-to-polymorphic-member type.
 *
 * @tparam MemberBase   the base type of the member.
 * @tparam Member       the concrete type of the member.
 * @tparam Object       the type that contains the member.
 *
 * @sa openvrml::node_impl_util::ptr_to_polymorphic_mem
 */

/**
 * @internal
 *
 * @var Member Object::* openvrml::node_impl_util::ptr_to_polymorphic_mem_impl::ptr_to_mem
 *
 * @brief Pointer-to-member.
 *
 * @tparam MemberBase   the base type of the member.
 * @tparam Member       the concrete type of the member.
 * @tparam Object       the type that contains the member.
 */

/**
 * @fn openvrml::node_impl_util::ptr_to_polymorphic_mem_impl::ptr_to_polymorphic_mem_impl(Member Object::* ptr_to_mem)
 *
 * @brief Construct.
 *
 * @param[in] ptr_to_mem    pointer-to-member.
 */

/**
 * @fn openvrml::node_impl_util::ptr_to_polymorphic_mem_impl::~ptr_to_polymorphic_mem_impl()
 *
 * @brief Destroy.
 *
 * @tparam MemberBase   the base type of the member.
 * @tparam Member       the concrete type of the member.
 * @tparam Object       the type that contains the member.
 */

/**
 * @fn MemberBase & openvrml::node_impl_util::ptr_to_polymorphic_mem_impl::deref(Object & obj)
 *
 * @brief Dereference.
 *
 * @tparam MemberBase   the base type of the member.
 * @tparam Member       the concrete type of the member.
 * @tparam Object       the type that contains the member.
 *
 * @return a reference to the base type of the member.
 */

/**
 * @overload const MemberBase & openvrml::node_impl_util::ptr_to_polymorphic_mem_impl::deref(const Object & obj)
 *
 * @return a @c const reference to the base type of the member.
 */


/**
 * @class openvrml::node_impl_util::abstract_node_type openvrml/node_impl_util.h
 *
 * @brief Abstract base for @c openvrml::node_type subclasses.
 *
 * This class is realized by instances of the @c node_type_impl class
 * template.
 *
 * @sa openvrml::node_impl_util::node_type_impl
 */

/**
 * @brief Construct.
 *
 * @param[in] metatype    the @c node_metatype.
 * @param[in] id            the @c node_type identifier.
 */
openvrml::node_impl_util::abstract_node_type::
abstract_node_type(const openvrml::node_metatype & metatype,
                   const std::string & id):
    node_type(metatype, id)
{}

/**
 * @brief Destroy.
 */
openvrml::node_impl_util::abstract_node_type::~abstract_node_type()
    OPENVRML_NOTHROW
{}

/**
 * @fn const openvrml::field_value & openvrml::node_impl_util::abstract_node_type::field_value(const openvrml::node & node, const std::string & id) const
 *
 * @brief @p node's field_value corresponding to @p id.
 *
 * @param[in] node  the @c openvrml::node for which to return the
 *                  @c openvrml::field_value.
 * @param[in] id    field identifier.
 * 
 * @return @p node's @c openvrml::field_value corresponding to
 *         the field identifier @p id.
 *
 * @exception openvrml::unsupported_interface   if @p node has no field
 *                                              @p id.
 */

/**
 * @fn const openvrml::event_listener & openvrml::node_impl_util::abstract_node_type::event_listener(openvrml::node & node, const std::string & id) const
 *
 * @brief @p node's @c openvrml::event_listener corresponding to
 *        the eventIn identifier @p id.
 *
 * @param[in] node  the @c openvrml::node for which to return the
 *                  @c openvrml::event_listener.
 * @param[in] id    eventIn identifier.
 * 
 * @return @p node's @c openvrml::event_listener corresponding to
 *         the eventIn identifier @p id.
 *
 * @exception openvrml::unsupported_interface   if @p node has no eventIn
 *                                              @p id.
 */

/**
 * @fn const openvrml::event_emitter & openvrml::node_impl_util::abstract_node_type::event_emitter(openvrml::node & node, const std::string & id) const
 *
 * @brief @p node's @c openvrml::event_emitter corresponding to
 *        the eventOut identifier @p id.
 *
 * @param[in] node  the @c openvrml::node for which to return the
 *                  @c openvrml::event_emitter.
 * @param[in] id    eventOut identifier.
 * 
 * @return @p node's @c openvrml::event_emitter corresponding to
 *         the eventOut identifier @p id.
 *
 * @exception openvrml::unsupported_interface   if @p node has no eventOut
 *                                              @p id.
 */


/**
 * @class openvrml::node_impl_util::node_type_impl openvrml/node_impl_util.h
 *
 * @brief A template for concrete @c node_type%s.
 *
 * @c node_type_impl is instantiated by
 * @c #OPENVRML_NODE_IMPL_UTIL_DEFINE_DO_CREATE_TYPE to provide a concrete
 * @c node_type implementation.  Most node implementations can simply use that
 * macro and consider this class template an implementation detail.
 *
 * @tparam Node a concrete node type.
 *
 * @sa OPENVRML_NODE_IMPL_UTIL_DEFINE_DO_CREATE_TYPE
 */

/**
 * @var class openvrml::node_impl_util::node_type_impl::event_listener_base<Node>
 *
 * @brief The @c event_listener_base class template accesses
 * @c node_type_impl<Node>::event_listener_map.
 */

/**
 * @var class openvrml::node_impl_util::node_type_impl::event_emitter_base<Node>
 *
 * @brief The @c event_emitter_base class template accesses
 * @c node_type_impl<Node>::event_emitter_map.
 */

/**
 * @typedef boost::shared_ptr<openvrml::node_impl_util::ptr_to_polymorphic_mem<openvrml::field_value, Node> > openvrml::node_impl_util::node_type_impl<Node>::field_ptr_ptr
 *
 * @brief A @c shared_ptr to a pointer-to-member wrapper
 *        template.
 */

/**
 * @typedef boost::shared_ptr<openvrml::node_impl_util::ptr_to_polymorphic_mem<openvrml::event_listener, Node> > openvrml::node_impl_util::node_type_impl<Node>::event_listener_ptr_ptr
 *
 * @brief A @c shared_ptr to a pointer-to-member wrapper
 *        template.
 */

/**
 * @typedef boost::shared_ptr<openvrml::node_impl_util::ptr_to_polymorphic_mem<openvrml::event_emitter, Node> > openvrml::node_impl_util::node_type_impl<Node>::event_emitter_ptr_ptr
 *
 * @brief A @c shared_ptr to a pointer-to-member wrapper
 *        template.
 */

/**
 * @internal
 *
 * @var openvrml::node_interface_set openvrml::node_impl_util::node_type_impl<Node>::interfaces_
 *
 * @brief The set of @c node_interfaces for the
 *        @c node_type.
 */

/**
 * @internal
 *
 * @typedef std::map<std::string, openvrml::node_impl_util::node_type_impl<Node>::field_ptr_ptr> openvrml::node_impl_util::node_type_impl<Node>::field_value_map_t
 *
 * @brief Map of pointers to @c openvrml::field_value node
 *        members.
 */

/**
 * @internal
 *
 * @typedef std::map<std::string, openvrml::node_impl_util::node_type_impl<Node>::event_listener_ptr_ptr> openvrml::node_impl_util::node_type_impl<Node>::event_listener_map_t
 *
 * @brief Map of pointers to @c openvrml::event_listener node
 *        members.
 */

/**
 * @internal
 *
 * @typedef std::map<std::string, openvrml::node_impl_util::node_type_impl<Node>::event_emitter_ptr_ptr> openvrml::node_impl_util::node_type_impl<Node>::event_emitter_map_t
 *
 * @brief Map of pointers to @c openvrml::event_emitter node
 *        members.
 */

/**
 * @internal
 *
 * @var openvrml::node_impl_util::node_type_impl<Node>::field_value_map_t openvrml::node_impl_util::node_type_impl<Node>::field_value_map
 *
 * @brief Map of pointers to @c openvrml::field_value node
 *        members.
 */

/**
 * @internal
 *
 * @var openvrml::node_impl_util::node_type_impl<Node>::event_listener_map_t openvrml::node_impl_util::node_type_impl<Node>::event_listener_map
 *
 * @brief Map of pointers to @c openvrml::event_listener node
 *        members.
 */

/**
 * @internal
 *
 * @var openvrml::node_impl_util::node_type_impl<Node>::event_emitter_map_t openvrml::node_impl_util::node_type_impl<Node>::event_emitter_map
 *
 * @brief Map of pointers to @c openvrml::event_emitter node
 *        members.
 */


/**
 * @class openvrml::node_impl_util::event_listener_base openvrml/node_impl_util.h
 *
 * @brief Abstract base for @c event_listener implementations.
 *
 * @c event_listener_base implements
 * @c event_listener::do_eventin_id.
 *
 * @tparam Node a concrete node type.
 */

/**
 * @internal
 *
 * @typedef openvrml::node_impl_util::node_type_impl<Node> openvrml::node_impl_util::event_listener_base<Node>::node_type_t
 *
 * @brief The concrete @c node_type.
 */

/**
 * @internal
 *
 * @typedef openvrml::node_impl_util::event_listener_base<Node>::node_type_t::event_listener_map_t openvrml::node_impl_util::event_listener_base<Node>::event_listener_map_t
 *
 * @brief The map of @c event_listeners.
 */

/**
 * @internal
 *
 * @struct openvrml::node_impl_util::event_listener_base::event_listener_equal_to
 *
 * @brief A model of
 *        <a href="http://www.sgi.com/tech/stl/AdaptablePredicate.html">
 *        Adaptable Predicate</a>.
 *
 * @par Model of
 * <a href="http://www.sgi.com/tech/stl/AdaptablePredicate.html">Adaptable
 * Predicate</a>
 */

/**
 * @var const openvrml::event_listener * openvrml::node_impl_util::event_listener_base<Node>::event_listener_equal_to::listener_
 *
 * @brief The @c event_listener to test against.
 */

/**
 * @fn openvrml::node_impl_util::event_listener_base<Node>::event_listener_equal_to::event_listener_equal_to(const node_event_listener & listener)
 *
 * @brief Construct.
 *
 * @param[in] listener  the @c event_listener.
 */

/**
 * @fn bool openvrml::node_impl_util::event_listener_base<Node>::event_listener_equal_to::operator()(const typename event_listener_equal_to::argument_type & arg) const
 *
 * @brief Test whether the @c event_listener dereferenced from
 *        @p arg.second is the same one the function object was constructed
 *        with.
 */

/**
 * @fn openvrml::node_impl_util::event_listener_base::event_listener_base(openvrml::node & n)
 *
 * @brief Construct.
 *
 * @param[in] n the @c node associated with the
 *              @c event_listener.
 */

/**
 * @fn openvrml::node_impl_util::event_listener_base::~event_listener_base()
 *
 * @brief Destroy.
 */

/**
 * @fn const std::string openvrml::node_impl_util::event_listener_base::do_eventin_id() const
 *
 * @brief The associated @c eventIn identifier.
 *
 * @return the associated @c eventIn identifier.
 */


/**
 * @class openvrml::node_impl_util::event_emitter_base openvrml/node_impl_util.h
 *
 * @brief Abstract base for @c event_emitter implementations.
 *
 * @c event_emitter_base implements
 * @c openvrml::event_emitter::do_eventout_id.
 *
 * @tparam Node a concrete node type.
 */

/**
 * @internal
 *
 * @var openvrml::node * openvrml::node_impl_util::event_emitter_base::node_
 *
 * @brief The @c node with which the @c event_emitter is associated.
 */

/**
 * @internal
 *
 * @typedef openvrml::node_impl_util::node_type_impl<Node> openvrml::node_impl_util::event_emitter_base::node_type_t
 *
 * @brief The concrete @c node_type.
 */

/**
 * @internal
 *
 * @typedef openvrml::node_impl_util::event_emitter_base::node_type_t::event_emitter_map_t openvrml::node_impl_util::event_emitter_base::event_emitter_map_t
 *
 * @brief The map of @c event_emitters.
 */

/**
 * @internal
 *
 * @struct openvrml::node_impl_util::event_emitter_base::event_emitter_equal_to
 *
 * @brief A model of
 *        <a href="http://www.sgi.com/tech/stl/AdaptablePredicate.html">
 *        Adaptable Predicate</a>.
 *
 * @par Model of
 * <a href="http://www.sgi.com/tech/stl/AdaptablePredicate.html">Adaptable
 * Predicate</a>
 */

/**
 * @internal
 *
 * @var const openvrml::node_impl_util::event_emitter_base<Node> * openvrml::node_impl_util::event_emitter_base::event_emitter_equal_to::emitter_
 *
 * @brief The @c event_emitter to test against.
 */

/**
 * @fn openvrml::node_impl_util::event_emitter_base::event_emitter_equal_to::event_emitter_equal_to(const event_emitter_base<Node> & emitter)
 *
 * @brief Construct.
 *
 * @param[in] emitter   the @c event_emitter.
 */

/**
 * @fn bool openvrml::node_impl_util::event_emitter_base::event_emitter_equal_to::operator()(const typename event_emitter_equal_to::argument_type & arg) const
 *
 * @brief Test whether the @c event_emitter dereferenced from
 *        @p arg.second is the same one the function object was constructed
 *        with.
 */

/**
 * @fn openvrml::node_impl_util::event_emitter_base::event_emitter_base(openvrml::node & n, const field_value & value)
 *
 * @brief Construct.
 *
 * @param[in] n     the @c node associated with the
 *                  @c event_emitter.
 * @param[in] value the field value associated with the
 *                  @c event_emitter.
 */

/**
 * @fn openvrml::node_impl_util::event_emitter_base::~event_emitter_base()
 *
 * @brief Destroy.
 */

/**
 * @fn openvrml::node & openvrml::node_impl_util::event_emitter_base::node() const
 *
 * @brief The node with which the @c event_emitter is associated.
 */

/**
 * @fn const std::string openvrml::node_impl_util::event_emitter_base::do_eventout_id() const
 *
 * @brief The associated @c eventOut identifier.
 *
 * @return the associated @c eventOut identifier.
 */


/**
 * @class openvrml::node_impl_util::abstract_node openvrml/node_impl_util.h
 *
 * @brief Abstract base class for node implementations.
 *
 * @c abstract_node encapsulates the mechanisms for field access and
 * mutation, event dispatch, and @c eventOut access.
 *
 * @tparam Derived  the type that inherits this class template.
 */

/**
 * @typedef Derived openvrml::node_impl_util::abstract_node::self_t
 *
 * @brief The derived type.
 */

/**
 * @typedef openvrml::node_field_value_listener<openvrml::sfbool> openvrml::node_impl_util::abstract_node::sfbool_listener
 *
 * @brief @c openvrml::sfbool listener.  Provided for convenience.
 */

/**
 * @typedef openvrml::node_field_value_listener<openvrml::sfcolor> openvrml::node_impl_util::abstract_node::sfcolor_listener
 *
 * @brief @c openvrml::sfcolor listener.  Provided for convenience.
 */

/**
 * @typedef openvrml::node_field_value_listener<openvrml::sffloat> openvrml::node_impl_util::abstract_node::sffloat_listener
 *
 * @brief @c openvrml::sffloat listener.  Provided for convenience.
 */

/**
 * @typedef openvrml::node_field_value_listener<openvrml::sfdouble> openvrml::node_impl_util::abstract_node::sfdouble_listener
 *
 * @brief @c openvrml::sfdouble listener.  Provided for convenience.
 */

/**
 * @typedef openvrml::node_field_value_listener<openvrml::sfimage> openvrml::node_impl_util::abstract_node::sfimage_listener
 *
 * @brief @c openvrml::sfimage listener.  Provided for convenience.
 */

/**
 * @typedef openvrml::node_field_value_listener<openvrml::sfint32> openvrml::node_impl_util::abstract_node::sfint32_listener
 *
 * @brief @c openvrml::sfint32 listener.  Provided for convenience.
 */

/**
 * @typedef openvrml::node_field_value_listener<openvrml::sfnode> openvrml::node_impl_util::abstract_node::sfnode_listener
 *
 * @brief @c openvrml::sfnode listener.  Provided for convenience.
 */

/**
 * @typedef openvrml::node_field_value_listener<openvrml::sfrotation> openvrml::node_impl_util::abstract_node::sfrotation_listener
 *
 * @brief @c openvrml::sfrotation listener.  Provided for convenience.
 */

/**
 * @typedef openvrml::node_field_value_listener<openvrml::sfstring> openvrml::node_impl_util::abstract_node::sfstring_listener
 *
 * @brief @c openvrml::sfstring listener.  Provided for convenience.
 */

/**
 * @typedef openvrml::node_field_value_listener<openvrml::sftime> openvrml::node_impl_util::abstract_node::sftime_listener
 *
 * @brief @c openvrml::sftime listener.  Provided for convenience.
 */

/**
 * @typedef openvrml::node_field_value_listener<openvrml::sfvec2f> openvrml::node_impl_util::abstract_node::sfvec2f_listener
 *
 * @brief @c openvrml::sfvec2f listener.  Provided for convenience.
 */

/**
 * @typedef openvrml::node_field_value_listener<openvrml::sfvec2d> openvrml::node_impl_util::abstract_node::sfvec2d_listener
 *
 * @brief @c openvrml::sfvec2d listener.  Provided for convenience.
 */

/**
 * @typedef openvrml::node_field_value_listener<openvrml::sfvec3f> openvrml::node_impl_util::abstract_node::sfvec3f_listener
 *
 * @brief @c openvrml::sfvec3f listener.  Provided for convenience.
 */

/**
 * @typedef openvrml::node_field_value_listener<openvrml::sfvec3d> openvrml::node_impl_util::abstract_node::sfvec3d_listener
 *
 * @brief @c openvrml::sfvec3d listener.  Provided for convenience.
 */

/**
 * @typedef openvrml::node_field_value_listener<openvrml::mfbool> openvrml::node_impl_util::abstract_node::mfbool_listener
 *
 * @brief @c openvrml::mfbool listener.  Provided for convenience.
 */

/**
 * @typedef openvrml::node_field_value_listener<openvrml::mfcolor> openvrml::node_impl_util::abstract_node::mfcolor_listener
 *
 * @brief @c openvrml::mfcolor listener.  Provided for convenience.
 */

/**
 * @typedef openvrml::node_field_value_listener<openvrml::mffloat> openvrml::node_impl_util::abstract_node::mffloat_listener
 *
 * @brief @c openvrml::mffloat listener.  Provided for convenience.
 */

/**
 * @typedef openvrml::node_field_value_listener<openvrml::mfdouble> openvrml::node_impl_util::abstract_node::mfdouble_listener
 *
 * @brief @c openvrml::mfdouble listener.  Provided for convenience.
 */

/**
 * @typedef openvrml::node_field_value_listener<openvrml::mfint32> openvrml::node_impl_util::abstract_node::mfint32_listener
 *
 * @brief @c openvrml::mfint32 listener.  Provided for convenience.
 */

/**
 * @typedef openvrml::node_field_value_listener<openvrml::mfnode> openvrml::node_impl_util::abstract_node::mfnode_listener
 *
 * @brief @c openvrml::mfnode listener.  Provided for convenience.
 */

/**
 * @typedef openvrml::node_field_value_listener<openvrml::mfrotation> openvrml::node_impl_util::abstract_node::mfrotation_listener
 *
 * @brief @c openvrml::mfrotation listener.  Provided for convenience.
 */

/**
 * @typedef openvrml::node_field_value_listener<openvrml::mfstring> openvrml::node_impl_util::abstract_node::mfstring_listener
 *
 * @brief @c openvrml::mfstring listener.  Provided for convenience.
 */

/**
 * @typedef openvrml::node_field_value_listener<openvrml::mftime> openvrml::node_impl_util::abstract_node::mftime_listener
 *
 * @brief @c openvrml::mftime listener.  Provided for convenience.
 */

/**
 * @typedef openvrml::node_field_value_listener<openvrml::mfvec2f> openvrml::node_impl_util::abstract_node::mfvec2f_listener
 *
 * @brief @c openvrml::mfvec2f listener.  Provided for convenience.
 */

/**
 * @typedef openvrml::node_field_value_listener<openvrml::mfvec2d> openvrml::node_impl_util::abstract_node::mfvec2d_listener
 *
 * @brief @c openvrml::mfvec2d listener.  Provided for convenience.
 */

/**
 * @typedef openvrml::node_field_value_listener<openvrml::mfvec3f> openvrml::node_impl_util::abstract_node::mfvec3f_listener
 *
 * @brief @c openvrml::mfvec3f listener.  Provided for convenience.
 */

/**
 * @typedef openvrml::node_field_value_listener<openvrml::mfvec3d> openvrml::node_impl_util::abstract_node::mfvec3d_listener
 *
 * @brief @c openvrml::mfvec3d listener.  Provided for convenience.
 */

/**
 * @class openvrml::node_impl_util::abstract_node::event_emitter openvrml/node_impl_util.h
 *
 * @brief Concrete event emitter class template.
 */

/**
 * @fn openvrml::node_impl_util::abstract_node::event_emitter::event_emitter(openvrml::node & node, const FieldValue & value)
 *
 * @brief Construct.
 *
 * @param[in] node  @c node from which events will be emitted.
 * @param[in] value associated field value.
 */

/**
 * @fn openvrml::node_impl_util::abstract_node::event_emitter::~event_emitter()
 *
 * @brief Destroy.
 */

/**
 * @typedef openvrml::node_impl_util::abstract_node::event_emitter<openvrml::sfbool> openvrml::node_impl_util::abstract_node::sfbool_emitter
 *
 * @brief @c openvrml::sfbool event emitter.
 */

/**
 * @typedef openvrml::node_impl_util::abstract_node::event_emitter<openvrml::sfcolor> openvrml::node_impl_util::abstract_node::sfcolor_emitter
 *
 * @brief @c openvrml::sfcolor event emitter.
 */

/**
 * @typedef openvrml::node_impl_util::abstract_node::event_emitter<openvrml::sfdouble> openvrml::node_impl_util::abstract_node::sfdouble_emitter
 *
 * @brief @c openvrml::sfdouble event emitter.
 */

/**
 * @typedef openvrml::node_impl_util::abstract_node::event_emitter<openvrml::sffloat> openvrml::node_impl_util::abstract_node::sffloat_emitter
 *
 * @brief @c openvrml::sffloat event emitter.
 */

/**
 * @typedef openvrml::node_impl_util::abstract_node::event_emitter<openvrml::sfimage> openvrml::node_impl_util::abstract_node::sfimage_emitter
 *
 * @brief @c openvrml::sfimage event emitter.
 */

/**
 * @typedef openvrml::node_impl_util::abstract_node::event_emitter<openvrml::sfint32> openvrml::node_impl_util::abstract_node::sfint32_emitter
 *
 * @brief @c openvrml::sfint32 event emitter.
 */

/**
 * @typedef openvrml::node_impl_util::abstract_node::event_emitter<openvrml::sfnode> openvrml::node_impl_util::abstract_node::sfnode_emitter
 *
 * @brief @c openvrml::sfnode event emitter.
 */

/**
 * @typedef openvrml::node_impl_util::abstract_node::event_emitter<openvrml::sfrotation> openvrml::node_impl_util::abstract_node::sfrotation_emitter
 *
 * @brief @c openvrml::sfrotation event emitter.
 */

/**
 * @typedef openvrml::node_impl_util::abstract_node::event_emitter<openvrml::sfstring> openvrml::node_impl_util::abstract_node::sfstring_emitter
 *
 * @brief @c openvrml::sfstring event emitter.
 */

/**
 * @typedef openvrml::node_impl_util::abstract_node::event_emitter<openvrml::sftime> openvrml::node_impl_util::abstract_node::sftime_emitter
 *
 * @brief @c openvrml::sftime event emitter.
 */

/**
 * @typedef openvrml::node_impl_util::abstract_node::event_emitter<openvrml::sfvec2d> openvrml::node_impl_util::abstract_node::sfvec2d_emitter
 *
 * @brief @c openvrml::sfvec2d event emitter.
 */

/**
 * @typedef openvrml::node_impl_util::abstract_node::event_emitter<openvrml::sfvec2f> openvrml::node_impl_util::abstract_node::sfvec2f_emitter
 *
 * @brief @c openvrml::sfvec2f event emitter.
 */

/**
 * @typedef openvrml::node_impl_util::abstract_node::event_emitter<openvrml::sfvec3d> openvrml::node_impl_util::abstract_node::sfvec3d_emitter
 *
 * @brief @c openvrml::sfvec3d event emitter.
 */

/**
 * @typedef openvrml::node_impl_util::abstract_node::event_emitter<openvrml::sfvec3f> openvrml::node_impl_util::abstract_node::sfvec3f_emitter
 *
 * @brief @c openvrml::sfvec3f event emitter.
 */

/**
 * @typedef openvrml::node_impl_util::abstract_node::event_emitter<openvrml::mfcolor> openvrml::node_impl_util::abstract_node::mfcolor_emitter
 *
 * @brief @c openvrml::mfcolor event emitter.
 */

/**
 * @typedef openvrml::node_impl_util::abstract_node::event_emitter<openvrml::mfdouble> openvrml::node_impl_util::abstract_node::mfdouble_emitter
 *
 * @brief @c openvrml::mfdouble event emitter.
 */

/**
 * @typedef openvrml::node_impl_util::abstract_node::event_emitter<openvrml::mffloat> openvrml::node_impl_util::abstract_node::mffloat_emitter
 *
 * @brief @c openvrml::mffloat event emitter.
 */

/**
 * @typedef openvrml::node_impl_util::abstract_node::event_emitter<openvrml::mfnode> openvrml::node_impl_util::abstract_node::mfnode_emitter
 *
 * @brief @c openvrml::mfnode event emitter.
 */

/**
 * @typedef openvrml::node_impl_util::abstract_node::event_emitter<openvrml::mfrotation> openvrml::node_impl_util::abstract_node::mfrotation_emitter
 *
 * @brief @c openvrml::mfrotation event emitter.
 */

/**
 * @typedef openvrml::node_impl_util::abstract_node::event_emitter<openvrml::mfstring> openvrml::node_impl_util::abstract_node::mfstring_emitter
 *
 * @brief @c openvrml::mfstring event emitter.
 */

/**
 * @typedef openvrml::node_impl_util::abstract_node::event_emitter<openvrml::mftime> openvrml::node_impl_util::abstract_node::mftime_emitter
 *
 * @brief @c openvrml::mftime event emitter.
 */

/**
 * @typedef openvrml::node_impl_util::abstract_node::event_emitter<openvrml::mfvec2d> openvrml::node_impl_util::abstract_node::mfvec2d_emitter
 *
 * @brief @c openvrml::mfvec2d event emitter.
 */

/**
 * @typedef openvrml::node_impl_util::abstract_node::event_emitter<openvrml::mfvec2f> openvrml::node_impl_util::abstract_node::mfvec2f_emitter
 *
 * @brief @c openvrml::mfvec2f event emitter.
 */

/**
 * @typedef openvrml::node_impl_util::abstract_node::event_emitter<openvrml::mfvec3d> openvrml::node_impl_util::abstract_node::mfvec3d_emitter
 *
 * @brief @c openvrml::mfvec3d event emitter.
 */

/**
 * @typedef openvrml::node_impl_util::abstract_node::event_emitter<openvrml::mfvec3f> openvrml::node_impl_util::abstract_node::mfvec3f_emitter
 *
 * @brief @c openvrml::mfvec3f event emitter.
 */

/**
 * @class openvrml::node_impl_util::abstract_node::exposedfield openvrml/node_impl_util.h
 *
 * @brief exposedField implementation.
 */

/**
 * @fn openvrml::node_impl_util::abstract_node::exposedfield::exposedfield(openvrml::node & node, const typename FieldValue::value_type & value)
 *
 * @brief Construct.
 *
 * @param[in] node  the node.
 * @param[in] value the initial value.
 */

/**
 * @fn openvrml::node_impl_util::abstract_node::exposedfield::exposedfield(const exposedfield<FieldValue> & obj)
 *
 * @brief Construct a copy.
 *
 * @param[in] obj   the instance to copy.
 */

/**
 * @fn openvrml::node_impl_util::abstract_node::exposedfield::~exposedfield()
 *
 * @brief Destroy.
 */

/**
 * @fn std::auto_ptr<openvrml::field_value> openvrml::node_impl_util::abstract_node::exposedfield::do_clone() const
 *
 * @brief Polymorphically construct a copy.
 */

/**
 * @var openvrml::node_impl_util::abstract_node::metadata
 *
 * @brief metadata exposedField.
 */

/**
 * @fn openvrml::node_impl_util::abstract_node::abstract_node(const node_type & type, const boost::shared_ptr<openvrml::scope> & scope)
 *
 * @brief Construct.
 *
 * @param[in] type  the @c node_type associated with this node.
 * @param[in] scope the @c scope to which the @c node belongs.
 */

/**
 * @fn openvrml::node_impl_util::abstract_node::~abstract_node()
 *
 * @brief Destroy.
 */

/**
 * @fn const openvrml::field_value & openvrml::node_impl_util::abstract_node::do_field(const std::string & id) const
 *
 * @brief Get a field value for a @c node.
 *
 * @param[in] id    a field name.
 *
 * @exception unsupported_interface  if the @c node has no @c field @p id.
 */

/**
 * @fn openvrml::event_listener & openvrml::node_impl_util::abstract_node::do_event_listener(const std::string & id)
 *
 * @brief Get an event listener.
 *
 * This method is called by @c node::event_listener.
 *
 * @param[in] id    @c eventIn identifier.
 *
 * @return the event listener.
 *
 * @exception unsupported_interface if the @c node has no @c eventIn @p id.
 */

/**
 * @fn openvrml::event_emitter & openvrml::node_impl_util::abstract_node::do_event_emitter(const std::string & id)
 *
 * @brief Get an event emitter.
 *
 * This method is called by @c node::event_emitter.
 *
 * @param[in] id    @c eventOut identifier.
 *
 * @return the event emitter.
 *
 * @exception unsupported_interface if the @c node has no @c eventOut @p id.
 */

/**
 * @class openvrml::node_impl_util::node_type_impl::field_ptr openvrml/node_impl_util.h
 *
 * @brief Concrete pointer-to-member wrapper.
 *
 * @tparam FieldMember  a @c field_value member of Node.
 */

/**
 * @fn openvrml::node_impl_util::node_type_impl::field_ptr::field_ptr(FieldMember Node::* ptr_to_mem)
 *
 * @brief Construct.
 *
 * @param[in] ptr_to_mem    a pointer to an @c openvrml::field_value
 *                          member.
 */

/**
 * @fn const typename openvrml::node_impl_util::node_type_impl::field_ptr_ptr openvrml::node_impl_util::node_type_impl::make_field_ptr_ptr(FieldMember DeducedNode::* ptr_to_mem)
 *
 * @brief Make a @c #field_ptr_ptr to a field member of a node.
 *
 * @tparam FieldMember  a @c field_value member of Node.
 * @tparam DeducedNode  the deduced type of the node may differ from its actual
 *                      concrete type in the contexts in which this function is
 *                      used.  We @c static_cast to the actual type.
 *
 * @param[in] ptr_to_mem    a pointer to an @c openvrml::field_value member.
 *
 * @return a @c #field_ptr_ptr to @p ptr_to_mem.
 */

/**
 * @class openvrml::node_impl_util::node_type_impl::event_listener_ptr openvrml/node_impl_util.h
 *
 * @brief Concrete pointer-to-member wrapper.
 *
 * @tparam EventListenerMember  an @c event_listener member of Node.
 */

/**
 * @fn openvrml::node_impl_util::node_type_impl::event_listener_ptr::event_listener_ptr(EventListenerMember Node::* ptr_to_mem)
 *
 * @brief Construct.
 *
 * @param[in] ptr_to_mem    a pointer to an
 *                          @c openvrml::event_listener member.
 */

/**
 * @fn const typename openvrml::node_impl_util::node_type_impl::event_listener_ptr_ptr openvrml::node_impl_util::node_type_impl::make_event_listener_ptr_ptr(EventListenerMember DeducedNode::* ptr_to_mem)
 *
 * @brief Make an @c #event_listener_ptr_ptr to a field member of a node.
 *
 * @tparam EventListenerMember  an @c event_listener member of Node.
 * @tparam DeducedNode          the deduced type of the node may differ from
 *                              its actual concrete type in the contexts in
 *                              which this function is used.  We @c static_cast
 *                              to the actual type.
 *
 * @param[in] ptr_to_mem    a pointer to an @c openvrml::event_listener member.
 *
 * @return a @c #event_listener_ptr_ptr to @p ptr_to_mem.
 */

/**
 * @class openvrml::node_impl_util::node_type_impl::event_emitter_ptr openvrml/node_impl_util.h
 *
 * @brief Concrete pointer-to-member wrapper.
 *
 * @tparam EventEmitterMember   the type of an @c openvrml::event_emitter
 *                              member of @p Node.
 */

/**
 * @fn openvrml::node_impl_util::node_type_impl::event_emitter_ptr::event_emitter_ptr(EventEmitterMember Node::* ptr_to_mem)
 *
 * @brief Construct.
 *
 * @param[in] ptr_to_mem    a pointer to an
 *                          @c openvrml::event_emitter member.
 */

/**
 * @fn const typename openvrml::node_impl_util::node_type_impl::event_emitter_ptr_ptr openvrml::node_impl_util::node_type_impl::make_event_emitter_ptr_ptr(EventEmitterMember DeducedNode::* ptr_to_mem)
 *
 * @brief Make an @c #event_emitter_ptr_ptr to a field member of a node.
 *
 * @tparam EventEmitterMember   an @c event_emitter member of @p Node.
 * @tparam DeducedNode          the deduced type of the node may differ from
 *                              its actual concrete type in the contexts in
 *                              which this function is used.  We @c static_cast
 *                              to the actual type.
 *
 * @param[in] ptr_to_mem    a pointer to an @c openvrml::event_emitter member.
 *
 * @return a @c #event_emitter_ptr_ptr to @p ptr_to_mem.
 */

/**
 * @fn openvrml::node_impl_util::node_type_impl::node_type_impl(const openvrml::node_metatype & metatype, const std::string & id)
 *
 * @brief Construct.
 *
 * @param[in] metatype  the @c node_metatype.
 * @param[in] id        the @c node_type identifier.
 */

/**
 * @fn openvrml::node_impl_util::node_type_impl::~node_type_impl()
 *
 * @brief Destroy.
 */

/**
 * @fn void openvrml::node_impl_util::node_type_impl::add_eventin(const openvrml::field_value::type_id type, const std::string & id, EventListenerMember DeducedNode::* event_listener)
 *
 * @brief Add an @c eventIn.
 *
 * @tparam EventListenerMember  the type of the @p event_listener member.
 * @tparam DeducedNode          the deduced type of the node of which the
 *                              event listener is a member.
 *
 * @param[in] type              the field value type.
 * @param[in] id                the @c eventIn identifier.
 * @param[in] event_listener    the @c openvrml::event_listener associated
 *                              with the @c eventIn.
 *
 * @exception std::invalid_argument if an interface with a conflicting @p id
 *                                  has already been added to the
 *                                  @c node_type.
 * @exception std::bad_alloc        if memory allocation fails.
 */

/**
 * @fn void openvrml::node_impl_util::node_type_impl::add_eventout(const openvrml::field_value::type_id type, const std::string & id, EventEmitterMember DeducedNode::* event_emitter)
 *
 * @brief Add an @c eventOut.
 *
 * @tparam EventEmitterMember   the type of the @p event_emitter member.
 * @tparam DeducedNode          the deduced type of the node of which the
 *                              event emitter is a member.
 *
 * @param[in] type          the field value type.
 * @param[in] id            the @c eventOut identifier.
 * @param[in] event_emitter the @c openvrml::event_emitter
 *                          associated with the @c eventOut.
 *
 * @exception std::invalid_argument if an interface with a conflicting
 *                                  @p id has already been added to the
 *                                  @c node_type.
 * @exception std::bad_alloc        if memory allocation fails.
 */

/**
 * @fn void openvrml::node_impl_util::node_type_impl::add_exposedfield(const openvrml::field_value::type_id type, const std::string & id, EventListenerMember DeducedNode::* event_listener, FieldMember DeducedNode::* field, EventEmitterMember DeducedNode::* event_emitter)
 *
 * @brief Add an @c exposedField.
 *
 * @tparam EventEmitterMember   the type of the @p event_emitter member.
 * @tparam FieldMember          the type of the @p field member.
 * @tparam EventListenerMember  the type of the @p event_listener member.
 * @tparam DeducedNode          the deduced type of the node of which the
 *                              event emitter is a member.
 *
 * @param[in] type              the field value type.
 * @param[in] id                the @c exposedField identifier.
 * @param[in] event_listener    the @c openvrml::event_listener
 *                              associated with the @c exposedField.
 * @param[in] field             the @c openvrml::field_value
 *                              associated with the @c exposedField.
 * @param[in] event_emitter     the @c openvrml::event_emitter
 *                              associated with the @c exposedField.
 *
 * @exception std::invalid_argument if an interface with a conflicting
 *                                  @p id has already been added to the
 *                                  @c node_type.
 * @exception std::bad_alloc        if memory allocation fails.
 */

/**
 * @overload void openvrml::node_impl_util::node_type_impl::add_exposedfield(const openvrml::field_value::type_id type, const std::string & id, ExposedfieldMember DeducedNode::* exposedfield)
 *
 * @brief Add an @c exposedField.
 *
 * @tparam ExposedfieldMember   the type of the @p exposedfield member.
 * @tparam DeducedNode          the deduced type of the node of which the
 *                              event emitter is a member.
 *
 * @param[in] type          the field value type.
 * @param[in] id            the @c exposedField identifier.
 * @param[in] exposedfield  the member associated with the @c exposedField.
 *
 * @exception std::invalid_argument if an interface with a conflicting
 *                                  @p id has already been added to the
 *                                  @c node_type.
 * @exception std::bad_alloc        if memory allocation fails.
 */

/**
 * @fn void openvrml::node_impl_util::node_type_impl::add_field(const openvrml::field_value::type_id type, const std::string & id, FieldMember DeducedNode::* field)
 *
 * @brief Add a @c field.
 *
 * @tparam FieldMember          the type of the @p field member.
 * @tparam DeducedNode          the deduced type of the node of which the
 *                              event emitter is a member.
 *
 * @param[in] type  the field value type.
 * @param[in] id    the field identifier.
 * @param[in] field the @c openvrml::field_value associated with the
 *                  @c field.
 *
 * @exception std::invalid_argument if an interface with a conflicting
 *                                  @p id has already been added to the
 *                                  @c node_type.
 * @exception std::bad_alloc        if memory allocation fails.
 */

/**
 * @fn const openvrml::field_value & openvrml::node_impl_util::node_type_impl::field_value(const openvrml::node & node, const std::string & id) const
 *
 * @brief @p node's @c openvrml::field_value corresponding to the
 *        field identifier @p id.
 *
 * Delegates to @c node_type_impl<Node>::do_field_value.
 *
 * @param[in] node  the @c openvrml::node for which to return the
 *                  @c openvrml::field_value.
 * @param[in] id    @c field identifier.
 * 
 * @return @p node's @c openvrml::field_value corresponding to
 *         the @c field identifier @p id.
 *
 * @exception openvrml::unsupported_interface   if @p node has no @c field
 *                                              @p id.
 */

/**
 * @fn const openvrml::field_value & openvrml::node_impl_util::node_type_impl::do_field_value(const Node & node, const std::string & id) const
 *
 * @brief @p node's @c openvrml::field_value corresponding to the
 *        field identifier @p id.
 *
 * @param[in] node  the node for which to return the
 *                  @c openvrml::field_value.
 * @param[in] id    @c field identifier.
 * 
 * @return @p node's @c openvrml::field_value corresponding to
 *         the @c field identifier @p id.
 *
 * @exception openvrml::unsupported_interface   if @p node has no @c field
 *                                              @p id.
 */

/**
 * @fn openvrml::event_listener & openvrml::node_impl_util::node_type_impl::event_listener(openvrml::node & node, const std::string & id) const
 *
 * @brief @p node's @c openvrml::event_listener corresponding to
 *        the @c eventIn identifier @p id.
 *
 * Delegates to
 * @c node_type_impl<Node>::do_event_listener.
 *
 * @param[in] node  the @c openvrml::node for which to return the
 *                  @c openvrml::event_listener.
 * @param[in] id    @c eventIn identifier.
 * 
 * @return @p node's @c openvrml::event_listener corresponding to
 *         the eventIn identifier @p id.
 *
 * @exception openvrml::unsupported_interface   if @p node has no @c eventIn
 *                                              @p id.
 */

/**
 * @fn openvrml::event_listener & openvrml::node_impl_util::node_type_impl::do_event_listener(Node & node, const std::string & id) const
 *
 * @brief @p node's @c openvrml::event_listener corresponding to
 *        the @c eventIn identifier @p id.
 *
 * @param[in] node  the @c openvrml::node for which to return the
 *                  @c openvrml::event_listener.
 * @param[in] id    @c eventIn identifier.
 * 
 * @return @p node's @c openvrml::event_listener corresponding to
 *         the @c eventIn identifier @p id.
 *
 * @exception openvrml::unsupported_interface   if @p node has no @c eventIn
 *                                              @p id.
 */

/**
 * @fn openvrml::event_emitter & openvrml::node_impl_util::node_type_impl::event_emitter(openvrml::node & node, const std::string & id) const
 *
 * @brief @p node's @c openvrml::event_emitter corresponding to
 *        the @c eventOut identifier @p id.
 *
 * Delegates to @c node_type_impl<Node>::do_event_emitter.
 *
 * @param[in] node  the @c openvrml::node for which to return the
 *                  @c openvrml::event_emitter.
 * @param[in] id    @c eventOut identifier.
 * 
 * @return @p node's @c openvrml::event_emitter corresponding to
 *         the @c eventOut identifier @p id.
 *
 * @exception openvrml::unsupported_interface   if @p node has no @c eventOut
 *                                              @p id.
 */

/**
 * @fn openvrml::event_emitter & openvrml::node_impl_util::node_type_impl::do_event_emitter(Node & node, const std::string & id) const
 *
 * @brief @p node's @c openvrml::event_emitter corresponding to
 *        the @c eventOut identifier @p id.
 *
 * Delegates to @c node_type_impl<Node>::do_event_emitter.
 *
 * @param[in] node  the @c openvrml::node for which to return the
 *                  @c openvrml::event_emitter.
 * @param[in] id    @c eventOut identifier.
 * 
 * @return @p node's @c openvrml::event_emitter corresponding to
 *         the @c eventOut identifier @p id.
 *
 * @exception openvrml::unsupported_interface   if @p node has no @c eventOut
 *                                              @p id.
 */

/**
 * @fn const openvrml::node_interface_set & openvrml::node_impl_util::node_type_impl::do_interfaces() const
 *
 * @brief The set of @c node_interfaces supported by the
 *        @c node_type.
 *
 * @return the set of @c node_interfaces supported by the
 *         @c node_type.
 */

/**
 * @fn const boost::intrusive_ptr<openvrml::node> openvrml::node_impl_util::node_type_impl::do_create_node(const boost::shared_ptr<openvrml::scope> & scope, const openvrml::initial_value_map & initial_values) const
 *
 * @brief Create a node instance.
 *
 * @param[in] scope             the @c scope the new node will belong to.
 * @param[in] initial_values    initial values for the new <code>node</code>'s
 *                              fields.
 *
 * @return a new node instance.
 *
 * @exception openvrml::unsupported_interface   if a field identifier in
 *                                              @p initial_values does not
 *                                              correspond to a field for the
 *                                              @c node_type.
 * @exception std::bad_cast                     if a field value type in
 *                                              @p initial_values is incorrect
 *                                              for the corresponding field for
 *                                              the @c node_type.
 * @exception std::bad_alloc                    if memory allocation fails.
 */


/**
 * @struct openvrml::node_impl_util::BindableNodeConcept openvrml/node_impl_util.h
 *
 * @brief Concept checking class to validate that a template parameter is a
 *        model of the Bindable Node concept.
 *
 * A Bindable Node is a node that has a member function @c bind that takes a
 * boolean value (the bind state) and a floating point value (the current
 * time).
 *
 * @par Notation
 * <table>
 *   <tr>
 *     <td>t</td>
 *     <td>An object whose type is a model of Bindable Node</td>
 *   </tr>
 *   <tr><td>bind_state</td><td>A boolean</td></tr>
 *   <tr><td>bind_time</td><td>A floating-point value</td></tr>
 * </table>
 *
 * @par Valid expressions
 * <table>
 *   <tr>
 *     <th>Name</th>
 *     <th>Expression</th>
 *     <th>Type requirements</th>
 *     <th>Return type</th>
 *   </tr>
 *   <tr>
 *     <td>Bind</td>
 *     <td><code>t.bind(bind_state, bind_time)</code></td>
 *     <td></td>
 *     <td><code>void</code></td>
 *   </tr>
 * </table>
 */

/**
 * @internal
 *
 * @var T * openvrml::node_impl_util::BindableNodeConcept::bindable_node
 */

/**
 * @fn void openvrml::node_impl_util::BindableNodeConcept<T>::constraints()
 *
 * @brief Validate that T is a model of the Bindable Node concept.
 */


/**
 * @class openvrml::node_impl_util::bound_node_stack openvrml/node_impl_util.h
 *
 * @brief A stack of bindable nodes.
 *
 * The node at the top of the stack is considered the @e active node.
 * @e Binding a node makes it the active node, moving it to the top of
 * the stack if it already exists in the stack.  @e Unbinding a node
 * removes it from the stack, regardless of its position in the stack.
 * See 4.6.10 of the VRML97 specification for further details of the
 * semantics.
 *
 * @tparam BindableNode a @link BindableNodeConcept Bindable Node@endlink.
 *
 * @sa http://www.web3d.org/x3d/specifications/vrml/ISO-IEC-14772-VRML97/part1/concepts.html#4.6.10
 */

/**
 * @internal
 *
 * @typedef std::stack<BindableNode *>::container_type openvrml::node_impl_util::bound_node_stack<BindableNode>::container_type
 *
 * @brief The container type.
 */

/**
 * @fn bool openvrml::node_impl_util::bound_node_stack<BindableNode>::bind(BindableNode & n, double timestamp)
 *
 * @brief Bind a node.
 *
 * Call @c top()->bind(false).  Push @p n onto the top of
 * the stack, making it the active node.  Call
 * @c n.bind(true).
 *
 * @post @c top() == &n
 *
 * @tparam BindableNode a @link BindableNodeConcept Bindable Node@endlink.
 *
 * @param[in,out] n         the node to bind.
 * @param[in]     timestamp the current time.
 *
 * @exception std::bad_alloc    if memory allocation fails.
 */

/**
 * @fn bool openvrml::node_impl_util::bound_node_stack<BindableNode>::unbind(BindableNode & n, double timestamp)
 *
 * @brief Unbind a node.
 *
 * Call @c n.bind(false).  Remove @p n from the top of the
 * stack. The next node on the stack becomes the active node.  Call
 * @c top()->bind(true).
 *
 * @post @c &n is not on the stack.
 *
 * @tparam BindableNode a @link BindableNodeConcept Bindable Node@endlink.
 *
 * @param[in,out] n         the node to unbind.
 * @param[in]     timestamp the current time.
 *
 * @exception std::bad_alloc    if memory allocation fails.
 */
