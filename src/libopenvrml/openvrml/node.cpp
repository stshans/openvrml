// -*- Mode: C++; indent-tabs-mode: nil; c-basic-offset: 4; fill-column: 78 -*-
//
// OpenVRML
//
// Copyright 1998  Chris Morley
// Copyright 2002, 2003, 2004, 2005, 2006, 2007, 2008  Braden McDaniel
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

# include "browser.h"
# include "scope.h"
# include "viewer.h"
# include <openvrml/local/node_metatype_registry_impl.h>
# include <openvrml/local/uri.h>
# include <openvrml/local/field_value_types.h>
# include <boost/array.hpp>
# include <boost/lexical_cast.hpp>
# include <boost/mpl/for_each.hpp>
# include <algorithm>
# include <sstream>

# ifdef HAVE_CONFIG_H
#   include <config.h>
# endif

/**
 * @file openvrml/node.h
 *
 * @brief Abstract node types and supporting types.
 */

/**
 * @class openvrml::unsupported_interface openvrml/node.h
 *
 * @brief Exception to indicate that a @c node interface is not supported.
 *
 * This exception is thrown by @c node::event_listener and
 * @c node::event_emitter to indicate that the node doesn't support the
 * interface through which the caller is trying to modify the node.  It is
 * also thrown by @c node_metatype::create_type if the class object doesn't
 * support an interface specified in the @c node_interface_set given to that
 * method.
 */

/**
 * @brief Construct.
 *
 * @param[in] interface_ a @c node_interface.
 */
openvrml::unsupported_interface::
unsupported_interface(const node_interface & interface_)
    OPENVRML_NOTHROW:
    std::logic_error("unsupported interface \""
                     + boost::lexical_cast<std::string>(interface_) + "\"")
{}

/**
 * @brief Construct.
 *
 * @param[in] type          the @c node_type.
 * @param[in] interface_id  the name of the interface that is not available.
 */
openvrml::unsupported_interface::
unsupported_interface(const node_type & type, const std::string & interface_id)
    OPENVRML_NOTHROW:
    std::logic_error(type.id() + " has no interface \"" + interface_id + '"')
{}

/**
 * @brief Construct.
 *
 * @param[in] type              the @c node_type.
 * @param[in] interface_type    the type of the interface that is not
 *                              available.
 * @param[in] interface_id      the name of the interface that is not
 *                              available.
 */
openvrml::unsupported_interface::
unsupported_interface(const node_type & type,
                      const node_interface::type_id interface_type,
                      const std::string & interface_id)
    OPENVRML_NOTHROW:
    std::logic_error(type.id() + " has no "
                     + boost::lexical_cast<std::string>(interface_type)
                     + " \"" + interface_id + '"')
{}

/**
 * @brief Destroy.
 */
openvrml::unsupported_interface::~unsupported_interface() throw ()
{}


/**
 * @class openvrml::node_interface openvrml/node.h
 *
 * @brief Type information for an interface of a @c node.
 */

/**
 * @enum openvrml::node_interface::type_id
 *
 * @brief Identify the type of interface.
 */

/**
 * @var openvrml::node_interface::type_id openvrml::node_interface::invalid_type_id
 *
 * @brief Used to indicate an invalid or unknown interface type.
 */

/**
 * @var openvrml::node_interface::type_id openvrml::node_interface::eventin_id
 *
 * @brief An @c eventIn.
 */

/**
 * @var openvrml::node_interface::type_id openvrml::node_interface::eventout_id
 *
 * @brief An @c eventOut.
 */

/**
 * @var openvrml::node_interface::type_id openvrml::node_interface::exposedfield_id
 *
 * @brief An @c exposedField.
 */

/**
 * @var openvrml::node_interface::type_id openvrml::node_interface::field_id
 *
 * @brief A @c field.
 */

namespace {

    typedef boost::array<const char *, 5> node_interface_type_id;

    const node_interface_type_id vrml97_node_interface_type_id_ = {
        "<invalid interface type>",
        "eventIn",
        "eventOut",
        "exposedField",
        "field"
    };

    const node_interface_type_id x3d_node_interface_type_id_ = {
        "<invalid interface type>",
        "inputOnly",
        "outputOnly",
        "inputOutput",
        "initializeOnly"
    };
}

/**
 * @brief Stream inserter.
 *
 * @relatesalso openvrml::node_interface
 *
 * If @p type is @c node_interface::invalid_type_id, @c failbit is set on
 * @p out.
 *
 * @param[in,out] out   an output stream.
 * @param[in]     type  a @c node interface type.
 *
 * @return @p out.
 */
std::ostream & openvrml::operator<<(std::ostream & out,
                                    const node_interface::type_id type)
{
    if (type == node_interface::invalid_type_id) {
        out.setstate(std::ios_base::failbit);
    } else {
        out << vrml97_node_interface_type_id_[type];
    }
    return out;
}

/**
 * @brief Stream extractor.
 *
 * @relatesalso node_interface
 *
 * @param[in,out] in    an input stream.
 * @param[out]    type  a @c node interface type.
 *
 * @return @p in.
 */
std::istream & openvrml::operator>>(std::istream & in,
                                    node_interface::type_id & type)
{
    using std::find;
    using std::string;

    string interface_type_id;
    in >> interface_type_id;

    node_interface_type_id::const_iterator pos =
        find(vrml97_node_interface_type_id_.begin(),
             vrml97_node_interface_type_id_.end(),
             interface_type_id);
    if (pos != vrml97_node_interface_type_id_.end()) {
        type = node_interface::type_id(
            pos - vrml97_node_interface_type_id_.begin());
    } else {
        pos = find(x3d_node_interface_type_id_.begin(),
                   x3d_node_interface_type_id_.end(),
                   interface_type_id);
        if (pos != x3d_node_interface_type_id_.end()) {
            type = node_interface::type_id(
                pos - x3d_node_interface_type_id_.begin());
        } else {
            in.setstate(std::ios_base::failbit);
        }
    }
    return in;
}


/**
 * @var openvrml::node_interface::type
 *
 * @brief The interface type.
 */

/**
 * @var openvrml::node_interface::field_type
 *
 * @brief The field data type handled by this interface.
 */

/**
 * @var openvrml::node_interface::id
 *
 * @brief The name of this interface.
 */

/**
 * @fn openvrml::node_interface::node_interface(type_id type, field_value::type_id field_type, const std::string & id)
 *
 * @brief Constructor.
 *
 * @param[in] type       the type of interface.
 * @param[in] field_type the field data type handled by the interface.
 * @param[in] id         the name of the interface.
 */

/**
 * @relatesalso openvrml::node_interface
 *
 * @brief Compare for equality.
 *
 * @param[in] lhs   a @c node_interface.
 * @param[in] rhs   a @c node_interface.
 *
 * @return @c true if the two @c node_interface%s are equal, @c false otherwise.
 */
bool openvrml::operator==(const node_interface & lhs,
                          const node_interface & rhs)
    OPENVRML_NOTHROW
{
    return lhs.type == rhs.type
        && lhs.field_type == rhs.field_type
        && lhs.id == rhs.id;
}

/**
 * @relatesalso openvrml::node_interface
 *
 * @brief Compare for openvrml::inequality.
 *
 * @param[in] lhs   a @c node_interface.
 * @param[in] rhs   a @c node_interface.
 *
 * @return @c true if the two @c node_interface%s are equal, @c false otherwise.
 */
bool openvrml::operator!=(const node_interface & lhs,
                          const node_interface & rhs)
    OPENVRML_NOTHROW
{
    return !(lhs == rhs);
}

/**
 * @relatesalso openvrml::node_interface
 *
 * @brief Stream output.
 *
 * @param[in,out] out           output stream.
 * @param[in]     interface_    @c node_interface.
 *
 * @return @p out.
 */
std::ostream & openvrml::operator<<(std::ostream & out,
                                    const node_interface & interface_)
{
    return out << interface_.type << ' ' << interface_.field_type << ' '
               << interface_.id;
}

/**
 * @relatesalso openvrml::node_interface
 *
 * @brief Stream input.
 *
 * @param[in,out] in            input stream.
 * @param[out]    interface_    @c node_interface.
 *
 * @return @p in.
 */
std::istream & openvrml::operator>>(std::istream & in,
                                    node_interface & interface_)
{
    return in >> interface_.type >> interface_.field_type >> interface_.id;
}


/**
 * @struct openvrml::node_interface_matches_eventin openvrml/node.h
 *
 * @brief Determine if a @c node_interface matches an @c eventIn identifier.
 *
 * @par Model of
 * <a href="http://www.sgi.com/tech/stl/AdaptableBinaryPredicate.html">
 * Adaptable Binary Predicate</a>,
 * <a href="http://www.sgi.com/tech/stl/DefaultConstructible.html">
 * Default Constructible</a>
 */

/**
 * @fn openvrml::node_interface_matches_eventin::result_type openvrml::node_interface_matches_eventin::operator()(const first_argument_type & interface_, const second_argument_type & eventin_id) const
 *
 * @brief Determine if a @c node_interface matches an @c eventIn identifier.
 *
 * A @c node_interface matches an @c eventIn identifier if:
 * - the <code>node_interface</code>'s @a type is @c node_interface::eventin_id
 *   and
 *   - the <code>node_interface</code>'s @a id is lexicographically equal to
 *     the @c eventIn identifier
 *   - or the <code>node_interface</code>'s @a id is lexicographically equal to
 *     the @c eventIn identifier with the string &ldquo;set_&rdquo; prepended.
 * - or, the <code>node_interface</code>'s @a type is
 *     @c node_interface::exposedfield_id and
 *   - the <code>node_interface</code>'s @a id is lexicographically equal to
 *     the @c eventIn identifier
 *   - or the <code>node_interface</code>'s @a id with the string
 *     &ldquo;set_&rdquo; prepended is lexicographically equal to the
 *     @c eventIn identifier.
 *
 * @param[in] interface_    @c node_interface.
 * @param[in] eventin_id    @c eventIn identifier.
 *
 * @return @c true if @p interface_ matches @p eventin_id; @c false otherwise.
 */


/**
 * @struct openvrml::node_interface_matches_eventout openvrml/node.h
 *
 * @brief Determine if a @c node_interface matches an @c eventOut identifier.
 *
 * @par Model of
 * <a href="http://www.sgi.com/tech/stl/AdaptableBinaryPredicate.html">
 * Adaptable Binary Predicate</a>,
 * <a href="http://www.sgi.com/tech/stl/DefaultConstructible.html">
 * Default Constructible</a>
 */

/**
 * @fn openvrml::node_interface_matches_eventout::result_type openvrml::node_interface_matches_eventout::operator()(const first_argument_type & interface_, const second_argument_type & eventout_id) const
 *
 * @brief Determine if a @c node_interface matches an @c eventOut identifier.
 *
 * A @c node_interface matches an @c eventOut identifier if:
 * - the <code>node_interface</code>'s @a type is
 *   @c node_interface::eventout_id and
 *   - the <code>node_interface</code>'s @a id is lexicographically equal to
 *     the @c eventOut identifier
 *   - or the <code>node_interface</code>'s @a id is lexicographically equal to
 *     the @c eventOut identifier with the string &ldquo;_changed&rdquo;
 *     appended.
 * - or, the <code>node_interface</code>'s @a type is
 *     @c node_interface::exposedfield_id and
 *   - the <code>node_interface</code>'s @a id is lexicographically equal to
 *     the @c eventOut identifier
 *   - or the <code>node_interface</code>'s @a id with the string
 *     &ldquo;_changed&rdquo; appended is lexicographically equal to the
 *     @c eventOut identifier.
 *
 * @param[in] interface_    @c node_interface.
 * @param[in] eventout_id   @c eventOut identifier.
 *
 * @return @c true if @p interface_ matches @p eventout_id; @c false otherwise.
 */


/**
 * @struct openvrml::node_interface_matches_exposedfield openvrml/node.h
 *
 * @brief Determine if a @c node_interface matches an @c exposedField
 * identifier.
 *
 * @par Model of
 * <a href="http://www.sgi.com/tech/stl/AdaptableBinaryPredicate.html">
 * Adaptable Binary Predicate</a>,
 * <a href="http://www.sgi.com/tech/stl/DefaultConstructible.html">
 * Default Constructible</a>
 */

/**
 * @fn openvrml::node_interface_matches_exposedfield::result_type openvrml::node_interface_matches_exposedfield::operator()(const first_argument_type & interface_, const second_argument_type & exposedfield_id) const
 *
 * @brief Determine if a @c node_interface matches an @c exposedField
 *        identifier.
 *
 * A @c node_interface matches an @c exposedField identifier if the
 * <code>node_interface</code>'s @a type is @c node_interface::exposedfield_id
 * and the <code>node_interface</code>'s @a id is lexicographically equal to
 * the @c exposedField identifier.
 *
 * @param[in] interface_        @c node_interface.
 * @param[in] exposedfield_id   @c exposedField identifier.
 *
 * @return @c true if @p interface_ matches @p exposedfield_id; @c false
 *         otherwise.
 */


/**
 * @struct openvrml::node_interface_matches_field openvrml/node.h
 *
 * @brief Determine if a @c node_interface matches an field
 *        identifier.
 *
 * @par Model of
 * <a href="http://www.sgi.com/tech/stl/AdaptableBinaryPredicate.html">
 * Adaptable Binary Predicate</a>,
 * <a href="http://www.sgi.com/tech/stl/DefaultConstructible.html">
 * Default Constructible</a>
 */

/**
 * @fn openvrml::node_interface_matches_field::result_type openvrml::node_interface_matches_field::operator()(const first_argument_type & interface_, const second_argument_type & field_id) const
 *
 * @brief Determine if a @c node_interface matches an field identifier.
 *
 * A @c node_interface matches a field identifier if the @c node_interface's
 * @a type is @c node_interface::field_id or @c node_interface::exposedfield_id
 * and the @c node_interface's @a id is lexicographically equal to the field
 * identifier.
 *
 * @param[in] interface_    @c node_interface.
 * @param[in] field_id      field identifier.
 *
 * @return @c true if @p interface_ matches @p field_id; @c false otherwise.
 */


/**
 * @struct openvrml::node_interface_compare openvrml/node.h
 *
 * @brief Function object to compare two @c node_interface%s based on their
 * id.
 *
 * @c node_interface_compare provides a <a
 * href="http://www.sgi.com/tech/stl/StrictWeakOrdering.html">Strict Weak
 * Ordering</a> for @c node_interface%s and ensures that @c exposedField
 * definitions appropriately encroach on the namespace of @c eventIn and @c
 * eventOut definitions.  That is, per 4.7 of the VRML97 spec: &ldquo;An
 * exposedField named &lsquo;zzz&rsquo; can be referred to as
 * &lsquo;set_zzz&rsquo; and treated as an eventIn, and can be referred to as
 * &lsquo;zzz_changed&rsquo; and treated as an eventOut.&rdquo;
 *
 * @c node_interface_compare is the comparator used by
 * <code>@link openvrml::node_interface_set node_interface_set@endlink</code>.
 *
 * @par Model of
 * <a href="http://www.sgi.com/tech/stl/AdaptableBinaryPredicate.html">
 * Adaptable Binary Predicate</a>,
 * <a href="http://www.sgi.com/tech/stl/StrictWeakOrdering.html">
 * Strict Weak Ordering</a>,
 * <a href="http://www.sgi.com/tech/stl/DefaultConstructible.html">
 * Default Constructible</a>
 *
 * @see node_interface_set
 */

/**
 * @fn openvrml::node_interface_compare::result_type openvrml::node_interface_compare::operator()(const first_argument_type & lhs, const second_argument_type & rhs) const
 *
 * @brief Compare two @c node_interface%s based on their id.
 *
 * @param[in] lhs   @c node_interface.
 * @param[in] rhs   @c node_interface.
 *
 * @return @c true if @p lhs.id is lexicographically less than @p rhs.id;
 *         @c false otherwise.
 */


/**
 * @typedef std::set<openvrml::node_interface, openvrml::node_interface_compare> openvrml::node_interface_set
 *
 * @brief A group of unique @c node_interface%s.
 *
 * @c node_interface_set%s are used to construct new @c node_type%s.  @c
 * node_type objects also expose their interfaces as a @c node_interface_set.
 * The interfaces in a @c node_interface_set are guaranteed to be unique and
 * nonconflicting.
 */

/**
 * @fn const openvrml::node_interface_set::const_iterator openvrml::find_interface(const node_interface_set & interfaces, const std::string & id)
 *
 * @brief Find an interface matching @p id.
 *
 * If no interface is found with an interface identifier that is an exact
 * match for @p id, this function will look for @c set_ and @c _changed
 * variants.  If @p interfaces contains a @c field @c zzz along with an @c
 * eventIn @c set_zzz and/or an @c eventOut @c zzz_changed, the @c eventIn or
 * @c eventOut will only be found if the @c set_zzz or @c zzz_changed form,
 * respectively, is used for @p id.
 *
 * @param[in] interfaces    a set of @c node_interface%s.
 * @param[in] id            the interface identifier to look for.
 *
 * @return a @c const_iterator to the interface, or @c node_interface_set::end
 *         if no interface is found.
 */


/**
 * @typedef openvrml::node_type_decls
 *
 * @brief A map of node type identifiers to their corresponding
 *        @c node_interface_set%s.
 */


/**
 * @class openvrml::node_metatype_id openvrml/node.h
 *
 * @brief Identifier for @c node_metatype%s.
 *
 * @c node_metatype identifiers take the following form:
 *
 * <pre>
 * absolute-uri ['#' proto-id ['#' proto-id [...]]]
 * </pre>
 *
 * A @c node_metatype identifier is basically like an absolute URI;
 * except the fragment identifier syntax has been extended to support referring
 * to nested @c PROTO%s.
 *
 * For example, supposing the following VRML world resides at
 * <code>%http://example.com/example.wrl</code>:
 *
 * <pre>
 * \#VRML V2.0 utf8
 *
 * PROTO Outer [] {
 *   PROTO Inner [] { Group {} }
 *   Group {}
 * }
 * </pre>
 *
 * The @c node_metatype_id string for @c Outer would be
 * <code>%http://example.com/example.wrl\#Outer</code>; and for @c Inner,
 * <code>%http://example.com/example.wrl\#Outer\#Inner</code>.
 */

/**
 * @internal
 *
 * @var std::string openvrml::node_metatype_id::id_
 *
 * @brief The identifier string.
 */

namespace {

    struct OPENVRML_LOCAL node_metatype_id_grammar :
        public boost::spirit::classic::grammar<node_metatype_id_grammar> {

        template <typename ScannerT>
        struct definition {
            typedef boost::spirit::classic::rule<ScannerT> rule_type;

            rule_type node_metatype_id;
            openvrml::local::absolute_uri_grammar<> absolute_uri;
            openvrml::local::uric_grammar uric;

            definition(const node_metatype_id_grammar & self);

            const boost::spirit::classic::rule<ScannerT> & start() const;
        };
    };

    template <typename ScannerT>
    node_metatype_id_grammar::definition<ScannerT>::
    definition(const node_metatype_id_grammar &)
    {
        node_metatype_id
            =   absolute_uri >> *('#' >> *uric)
            ;
    }

    template <typename ScannerT>
    const boost::spirit::classic::rule<ScannerT> &
    node_metatype_id_grammar::definition<ScannerT>::start() const
    {
        return this->node_metatype_id;
    }
}

/**
 * @brief Construct from a <code>const&nbsp;char&nbsp;*</code>.
 *
 * @param[in] id    the identifier.
 *
 * @exception std::invalid_argument if @p id is not a valid
 *                                  @c node_metatype identifier.
 * @exception std::bad_alloc        if memory allocation fails.
 *
 * @todo Need to make sure the fragment part is valid.
 */
openvrml::node_metatype_id::node_metatype_id(const char * id)
    OPENVRML_THROW2(std::invalid_argument, std::bad_alloc):
    id_(id)
{
    using namespace boost::spirit::classic;

    node_metatype_id_grammar g;
    if (!parse(this->id_.begin(), this->id_.end(), g, space_p).full) {
        throw std::invalid_argument('<' + this->id_ + "> is not a valid "
                                    "node_metatype identifier");
    }
}

/**
 * @brief Construct from a @c std::string.
 *
 * @param[in] id    the identifier.
 *
 * @exception std::invalid_argument if @p id is not a valid
 *                                  @c node_metatype identifier.
 * @exception std::bad_alloc        if memory allocation fails.
 *
 * @todo Need to make sure the fragment part is valid.
 */
openvrml::node_metatype_id::node_metatype_id(const std::string & id)
    OPENVRML_THROW2(std::invalid_argument, std::bad_alloc):
    id_(id)
{
    using namespace boost::spirit::classic;

    node_metatype_id_grammar g;
    if (!parse(this->id_.begin(), this->id_.end(), g, space_p).full) {
        throw std::invalid_argument('<' + this->id_ + "> is not a valid "
                                    "node_metatype identifier");
    }
}

/**
 * @brief Convert to a @c std::string.
 *
 * @return the @c node_metatype identifier as a @c std::string.
 */
openvrml::node_metatype_id::operator std::string() const
{
    return this->id_;
}

/**
 * @relatesalso openvrml::node_metatype_id
 *
 * @param[in] lhs
 * @param[in] rhs
 *
 * @return @c true if @p lhs and @p rhs are equal, @c false otherwise.
 */
bool openvrml::operator==(const node_metatype_id & lhs,
                          const node_metatype_id & rhs)
    OPENVRML_NOTHROW
{
    return lhs.id_ == rhs.id_;
}

/**
 * @relatesalso openvrml::node_metatype_id
 *
 * @param[in] lhs
 * @param[in] rhs
 *
 * @return @c true if @p lhs and @p rhs are not equal, @c false otherwise.
 */
bool openvrml::operator!=(const node_metatype_id & lhs,
                          const node_metatype_id & rhs)
    OPENVRML_NOTHROW
{
    return !(lhs == rhs);
}


/**
 * @class openvrml::node_metatype openvrml/node.h
 *
 * @brief A class object for node instances.
 *
 * @c node_metatype can be thought of as a &ldquo;supertype&rdquo; of sorts.
 * A given node implementation can support as many node types as there are
 * unique combinations of the interfaces it supports.  The most readily
 * apparent role of the @c node_metatype object for a node implementation is
 * to serve as a factory for these @c node_type%s.
 */

/**
 * @internal
 *
 * @var const std::string openvrml::node_metatype::id_
 *
 * @brief @c node_metatype identifier.
 */

/**
 * @internal
 *
 * @var openvrml::browser * const openvrml::node_metatype::browser_
 *
 * @brief The @c browser associated with this @c node_metatype.
 */

/**
 * @brief Constructor.
 *
 * A @c node_metatype is constructed using a @c browser.  All @c node instances
 * that share a particular @c node_metatype &ldquo;belong to&rdquo; the
 * @c browser associated with the @c node_metatype.
 *
 * @param[in] id    an identifier unique to @p b.
 * @param[in] b     the @c browser to be associated with the @c node_metatype.
 */
openvrml::node_metatype::node_metatype(const node_metatype_id & id,
                                       openvrml::browser & b)
    OPENVRML_NOTHROW:
    id_(id),
    browser_(&b)
{}

/**
 * @brief Destructor.
 */
openvrml::node_metatype::~node_metatype() OPENVRML_NOTHROW
{}

/**
 * @brief Identifier.
 *
 * @return the @c node_metatype identifier.
 */
const openvrml::node_metatype_id & openvrml::node_metatype::id() const
    OPENVRML_NOTHROW
{
    return this->id_;
}

/**
 * @brief The @c browser associated with this @c node_metatype.
 *
 * @return the @c browser associated with this @c node_metatype.
 */
openvrml::browser & openvrml::node_metatype::browser() const OPENVRML_NOTHROW
{
    assert(this->browser_);
    return *this->browser_;
}

/**
 * @brief <code>node_metatype</code>-specific initialization.
 *
 * This method is called during initialization of a @c browser object with a
 * new root @c scene.  It is called after the individual @c node instances
 * have been initialized, and before the world starts running.  It delegates
 * to @c #do_initialize.
 *
 * @param[in,out] initial_viewpoint the @c viewpoint_node that should be bound
 *                                  initially; or 0 if the default
 *                                  @c viewpoint_node should be bound.
 * @param[in] time                  the current time.
 */
void openvrml::node_metatype::initialize(viewpoint_node * initial_viewpoint,
                                         const double time)
    OPENVRML_NOTHROW
{
    this->do_initialize(initial_viewpoint, time);
}

/**
 * @brief <code>node_metatype</code>-specific initialization.
 *
 * Node implementations should override this method to perform any
 * <code>node_metatype</code>-wide initialization.
 *
 * @param[in,out] initial_viewpoint the @c viewpoint_node that should be
 *                                  bound initially; or 0 if the default
 *                                  @c viewpoint_node should be bound.
 * @param[in] time                  the current time.
 *
 * @sa node_metatype::initialize
 */
void openvrml::node_metatype::do_initialize(viewpoint_node *, double)
    OPENVRML_NOTHROW
{}

/**
 * @brief <code>node_metatype</code>-specific rendering.
 *
 * This function delegates to @c #do_render.
 *
 * @param[in,out] v    the @c viewer to which to render.
 */
void openvrml::node_metatype::render(viewer & v) const OPENVRML_NOTHROW
{
    this->do_render(v);
}

/**
 * @brief <code>node_metatype</code>-specific rendering.
 *
 * The default implementation of this method does nothing.
 *
 * @param[in,out] v    the @c viewer to which to render.
 *
 * @sa node_metatype::render
 */
void openvrml::node_metatype::do_render(viewer &) const OPENVRML_NOTHROW
{}

/**
 * @brief Create a new @c node_type.
 *
 * @c node_type%s can be said to subset the master type provided by the
 * @c node_metatype.  Each @c node_metatype instance can support certain
 * @c node interfaces; the @c node_interface_set passed to @c #create_type
 * must be a subset of those supported interfaces.
 *
 * This function delegates to @c #do_create_type.
 *
 * @param[in] id            the name for the new @c node_type.
 * @param[in] interfaces    a @c node_interface_set containing the
 *                          interfaces for the new type.
 *
 * @return a newly created @c node_type.
 *
 * @exception unsupported_interface if the @c node_metatype cannot
 *                                  support one of the @c node_interface%s in
 *                                  @p interfaces.
 * @exception std::bad_alloc        if memory allocation fails.
 *
 * @sa http://boost.org/libs/smart_ptr/shared_ptr.htm
 */
const boost::shared_ptr<openvrml::node_type>
openvrml::node_metatype::create_type(const std::string & id,
                                  const node_interface_set & interfaces)
    OPENVRML_THROW2(unsupported_interface, std::bad_alloc)
{
    return this->do_create_type(id, interfaces);
}

/**
 * @fn const boost::shared_ptr<openvrml::node_type> openvrml::node_metatype::do_create_type(const std::string & id, const node_interface_set & interfaces) const
 *
 * @brief Create a new @c node_type.
 *
 * Most %node implementations can use
 * @c #OPENVRML_NODE_IMPL_UTIL_DEFINE_DO_CREATE_TYPE to implement this function.
 *
 * @param[in] id            the name for the new @c node_type.
 * @param[in] interfaces    a @c node_interface_set containing the
 *                          interfaces for the new type.
 *
 * @return a newly created @c node_type.
 *
 * @exception unsupported_interface if the @c node_metatype cannot support one
 *                                  of the @c node_interface%s in
 *                                  @p interfaces.
 * @exception std::bad_alloc        if memory allocation fails.
 *
 * @sa #create_type
 * @sa OPENVRML_NODE_IMPL_UTIL_DEFINE_DO_CREATE_TYPE
 * @sa http://boost.org/libs/smart_ptr/shared_ptr.htm
 */

/**
 * @brief Shut down.
 *
 * This function is called during destruction of the @c browser, after the
 * root @c scene has been shut down.  This function delegates to
 * @c #do_shutdown.
 *
 * @param[in] time  the current time.
 */
void openvrml::node_metatype::shutdown(const double time) OPENVRML_NOTHROW
{
    this->do_shutdown(time);
}

/**
 * @brief Shut down.
 *
 * This function is called by @c #shutdown.
 *
 * @param[in] time  the current time.
 */
void openvrml::node_metatype::do_shutdown(double) OPENVRML_NOTHROW
{}


/**
 * @class openvrml::null_node_metatype openvrml/node.h
 *
 * @brief A placeholder @c node_metatype.
 *
 * The @c null_node_metatype is provided for convenience for the uncommon (but
 * not inconceivable) situation where one needs something that acts like a
 * @c node, yet isn't a full-fleged node with proper @c node_metatype and
 * @c node_type implementations.
 *
 * @sa openvrml::null_node_type
 */

/**
 * @brief Construct.
 *
 * @param browser a @c browser.
 */
openvrml::null_node_metatype::null_node_metatype(openvrml::browser & browser)
    OPENVRML_NOTHROW:
    node_metatype("urn:X-openvrml:node:null", browser)
{}

/**
 * @brief Destroy.
 */
openvrml::null_node_metatype::~null_node_metatype() OPENVRML_NOTHROW
{}

/**
 * @brief Do not call.
 *
 * @warning Correct code will not call this function.
 */
const boost::shared_ptr<openvrml::node_type>
openvrml::null_node_metatype::
do_create_type(const std::string &, const node_interface_set &) const
    OPENVRML_NOTHROW
{
    assert(false);
    static const boost::shared_ptr<node_type> type;
    return type;
}


/**
 * @typedef openvrml::initial_value_map
 *
 * @brief A map of the initial values with which a @c node is instantiated.
 */


/**
 * @class openvrml::node_type openvrml/node.h
 *
 * @brief Type information object for @c node%s.
 *
 * Each implementation of a %node in %OpenVRML must have an associated
 * concrete @c node_type that is capable of creating @c node%s with any subset
 * of the implementation's supported %node interfaces.  Because these can be
 * somewhat tedious to create, %OpenVRML includes a good deal of machinery to
 * facilitate the implementation of these classes.  For most %node
 * implementations, using @c #OPENVRML_NODE_IMPL_UTIL_DEFINE_DO_CREATE_TYPE to
 * implement @c node_metatype::do_create_type will generate an appropriate
 * concrete @c node_type.
 *
 * @sa node_metatype::create_type
 * @sa OPENVRML_NODE_IMPL_UTIL_DEFINE_DO_CREATE_TYPE
 */

/**
 * @internal
 *
 * @var openvrml::node_metatype & openvrml::node_type::metatype_
 *
 * @brief The class object associated with the @c node_type.
 */

/**
 * @internal
 *
 * @var const std::string openvrml::node_type::id_
 *
 * @brief The name of the @c node_type.
 */

/**
 * @brief Constructor.
 *
 * @param[in] c     the class object associated with the @c node_type.
 * @param[in] id    the name for the @c node_type.
 *
 * @exception std::bad_alloc    if memory allocation fails.
 */
openvrml::node_type::node_type(const node_metatype & c,
                               const std::string & id)
    OPENVRML_THROW1(std::bad_alloc):
    metatype_(c),
    id_(id)
{}

/**
 * @brief Destructor.
 */
openvrml::node_type::~node_type() OPENVRML_NOTHROW
{}

/**
 * @brief The class object associated with the @c node_type.
 *
 * @return the class object associated with the @c node_type.
 */
const openvrml::node_metatype & openvrml::node_type::metatype() const
    OPENVRML_NOTHROW
{
    return this->metatype_;
}

/**
 * @brief The name of the @c node_type.
 *
 * @return the name of the @c node_type.
 */
const std::string & openvrml::node_type::id() const OPENVRML_NOTHROW
{
    return this->id_;
}

/**
 * @brief Get the set of interfaces for the @c node_type.
 *
 * This function delegates to @c #do_interfaces.
 *
 * @return the set of interfaces.
 */
const openvrml::node_interface_set & openvrml::node_type::interfaces() const
    OPENVRML_NOTHROW
{
    return this->do_interfaces();
}

/**
 * @fn const openvrml::node_interface_set & openvrml::node_type::do_interfaces() const
 *
 * @brief Get the set of interfaces for the @c node_type.
 *
 * Subclasses must implement this function.
 *
 * @return the set of interfaces.
 */

/**
 * @brief Create a new node with this @c node_type.
 *
 * @param[in] scope             the @c scope to which the new @c node
 *                              should belong.
 * @param[in] initial_values    a map of initial values for the
 *                              <code>node</code>'s fields and
 *                              @c exposedField%s.
 *
 * @return a @c boost::intrusive_ptr to a new node.
 *
 * @exception unsupported_interface if @p initial_values specifies a field
 *                                  name that is not supported by the node
 *                                  type.
 * @exception std::bad_cast         if a value in @p initial_values is the
 *                                  wrong type.
 * @exception std::bad_alloc        if memory allocation fails.
 *
 * @sa http://boost.org/libs/smart_ptr/intrusive_ptr.html
 */
const boost::intrusive_ptr<openvrml::node>
openvrml::node_type::
create_node(const boost::shared_ptr<scope> & scope,
            const initial_value_map & initial_values) const
    OPENVRML_THROW3(unsupported_interface, std::bad_cast, std::bad_alloc)
{
    return this->do_create_node(scope, initial_values);
}

/**
 * @fn const boost::intrusive_ptr<openvrml::node> openvrml::node_type::do_create_node(const boost::shared_ptr<scope> & scope, const initial_value_map & initial_values) const
 *
 * @brief Create a new node with this @c node_type.
 *
 * Subclasses must implement this function.
 *
 * @param[in] scope             the @c scope to which the new
 *                              @c node should belong.
 * @param[in] initial_values    a map of initial values for the
 *                              <code>node</code>'s fields and
 *                              @c exposedField%s.
 *
 * @return a @c boost::intrusive_ptr to a new node.
 *
 * @exception unsupported_interface if @p initial_values specifies a field
 *                                  name that is not supported by the node
 *                                  type.
 * @exception std::bad_cast         if a value in @p initial_values is the
 *                                  wrong type.
 * @exception std::bad_alloc        if memory allocation fails.
 *
 * @sa http://boost.org/libs/smart_ptr/intrusive_ptr.html
 */

/**
 * @relatesalso openvrml::node_type
 *
 * @brief Compare for equality.
 *
 * Two @c node_type%s @c t and @c u are considered equal if all of the
 * following are true:
 *
 *   - <code>t.id() == u.id()</code>
 *   - <code>t.interfaces() == u.interfaces()</code>
 *   - <code>t.metatype().id()</code> is in the set of identifiers
 *      associated with @c u in the <code>browser</code>'s @c node_metatype map.
 *
 * Note that the latter requirement makes this comparison a rather expensive
 * operation.
 *
 * @param[in] lhs
 * @param[in] rhs
 *
 * @return @c true if @p lhs and @p rhs are equal; @c false otherwise.
 */
bool openvrml::operator==(const node_type & lhs, const node_type & rhs)
    OPENVRML_NOTHROW
{
    if (lhs.id() != rhs.id()) { return false; }
    if (lhs.interfaces() != rhs.interfaces()) { return false; }

    const std::vector<node_metatype_id> ids =
        rhs.metatype().browser()
        .node_metatype_registry_->impl_->node_metatype_ids(rhs.metatype());
    const std::vector<node_metatype_id>::const_iterator pos =
        std::find(ids.begin(), ids.end(), lhs.metatype().id());
    return pos != ids.end();
}

/**
 * @relatesalso openvrml::node_type
 *
 * @brief Compare for inequality.
 *
 * @param[in] lhs
 * @param[in] rhs
 *
 * @return @c true if @p lhs and @p rhs are not equal; @c false otherwise.
 */
bool openvrml::operator!=(const node_type & lhs, const node_type & rhs)
    OPENVRML_NOTHROW
{
    return !(lhs == rhs);
}


/**
 * @class openvrml::null_node_type openvrml/node.h
 *
 * @brief A placeholder @c node_type.
 *
 * The @c null_node_type is provided for convenience for the uncommon (but not
 * inconceivable) situation where one needs something that acts like a
 * @c node, yet isn't a full-fleged node with proper @c node_metatype and
 * @c node_type implementations.
 *
 * @sa openvrml::null_node_metatype
 */

/**
 * @brief Construct.
 */
openvrml::null_node_type::null_node_type(null_node_metatype & metatype)
    OPENVRML_NOTHROW:
    node_type(metatype, std::string())
{}

/**
 * @brief Destroy.
 */
openvrml::null_node_type::~null_node_type() OPENVRML_NOTHROW
{}

/**
 * @brief Do not call.
 *
 * @warning Correct code will not call this function.
 */
const openvrml::node_interface_set &
openvrml::null_node_type::do_interfaces() const OPENVRML_NOTHROW
{
    assert(false);
    static const node_interface_set interfaces;
    return interfaces;
}

/**
 * @brief Do not call.
 *
 * @warning Correct code will not call this function.
 */
const boost::intrusive_ptr<openvrml::node>
openvrml::null_node_type::
do_create_node(const boost::shared_ptr<openvrml::scope> &,
               const initial_value_map &) const
    OPENVRML_NOTHROW
{
    assert(false);
    static const boost::intrusive_ptr<node> node;
    return node;
}


/**
 * @class openvrml::field_value_type_mismatch openvrml/node.h
 *
 * @brief Thrown when field value types do not match, generally in a @c ROUTE
 *      or @c IS.
 */

/**
 * @brief Constructor.
 */
openvrml::field_value_type_mismatch::field_value_type_mismatch():
    std::logic_error("field value types do not match")
{}

/**
 * @brief Destructor.
 */
openvrml::field_value_type_mismatch::~field_value_type_mismatch() throw ()
{}


/**
 * @typedef std::deque<openvrml::node *> openvrml::node_path
 *
 * @brief A path to a @c node in the @c scene starting with one of the @c
 *        scene root @c node%s and ending with the objective @c node.
 */


/**
 * @fn To * openvrml::node_cast(node * n)
 *
 * @relatesalso openvrml::node
 *
 * @brief Downcast a @c node to one of the abstract @c node types.
 *
 * @tparam To   an abstract @c node type.
 *
 * @param[in] n a @c node.
 *
 * @return a pointer to the downcast @c node, or 0 if the cast fails.
 */

/**
 * @class openvrml::node openvrml/node.h
 *
 * @brief A @c node in the scene graph.
 */

/**
 * @fn std::ostream & openvrml::node::operator<<(std::ostream & out, const node & n)
 *
 * @brief Stream output.
 */

/**
 * @fn openvrml::script_node * openvrml::node::node_cast<script_node *>(node * n)
 *
 * @brief Cast to a @c script_node.
 */

/**
 * @fn openvrml::appearance_node * openvrml::node::node_cast<appearance_node *>(node * n)
 *
 * @brief Cast to a @c appearance_node.
 */

/**
 * @fn openvrml::child_node * openvrml::node::node_cast<child_node *>(node * n)
 *
 * @brief Cast to a @c child_node.
 */

/**
 * @fn openvrml::color_node * openvrml::node::node_cast<color_node *>(node * n)
 *
 * @brief Cast to a @c color_node.
 */

/**
 * @fn openvrml::color_rgba_node * openvrml::node::node_cast<color_rgba_node *>(node * n)
 *
 * @brief Cast to a @c color_rgba_node.
 */

/**
 * @fn openvrml::coordinate_node * openvrml::node::node_cast<coordinate_node *>(node * n)
 *
 * @brief Cast to a @c coordinate_node.
 */

/**
 * @fn openvrml::font_style_node * openvrml::node::node_cast<font_style_node *>(node * n)
 *
 * @brief Cast to a @c font_style_node.
 */

/**
 * @fn openvrml::geometry_node * openvrml::node::node_cast<geometry_node *>(node * n)
 *
 * @brief Cast to a @c geometry_node.
 */

/**
 * @fn openvrml::grouping_node * openvrml::node::node_cast<grouping_node *>(node * n)
 *
 * @brief Cast to a @c grouping_node.
 */

/**
 * @fn openvrml::material_node * openvrml::node::node_cast<material_node *>(node * n)
 *
 * @brief Cast to a @c material_node.
 */

/**
 * @fn openvrml::navigation_info_node * openvrml::node::node_cast<navigation_info_node *>(node * n)
 *
 * @brief Cast to a @c navigation_info_node.
 */

/**
 * @fn openvrml::normal_node * openvrml::node::node_cast<normal_node *>(node * n)
 *
 * @brief Cast to a @c normal_node.
 */

/**
 * @fn openvrml::sound_source_node * openvrml::node::node_cast<sound_source_node *>(node * n)
 *
 * @brief Cast to a @c sound_source_node.
 */

/**
 * @fn openvrml::texture_node * openvrml::node::node_cast<texture_node *>(node * n)
 *
 * @brief Cast to a @c texture_node.
 */

/**
 * @fn openvrml::texture_coordinate_node * openvrml::node::node_cast<texture_coordinate_node *>(node * n)
 *
 * @brief Cast to a @c texture_coordinate_node.
 */

/**
 * @fn openvrml::texture_transform_node * openvrml::node::node_cast<texture_transform_node *>(node * n)
 *
 * @brief Cast to a @c texture_transform_node.
 */

/**
 * @fn openvrml::transform_node * openvrml::node::node_cast<transform_node *>(node * n)
 *
 * @brief Cast to a @c transform_node.
 */

/**
 * @fn openvrml::viewpoint_node * openvrml::node::node_cast<viewpoint_node *>(node * n)
 *
 * @brief Cast to a @c viewpoint_node.
 */

/**
 * @internal
 *
 * @var class openvrml::node::local::proto_node
 *
 * @brief A @c PROTO instance.
 */

/**
 * @internal
 *
 * @var class openvrml::node::exposedfield<FieldValue>
 *
 * @brief @c exposedfield<FieldValue>::do_process_event calls
 *        @c node::emit_event.
 *
 * @tparam FieldValue   a concrete @c field_value.
 */

namespace {

    class OPENVRML_LOCAL self_ref_node : public openvrml::node {
    public:
        self_ref_node();
        virtual ~self_ref_node() OPENVRML_NOTHROW;

    private:
        virtual const openvrml::field_value &
        do_field(const std::string & id) const
            OPENVRML_THROW1(openvrml::unsupported_interface);
        virtual void
            do_assign_field(const std::string & id, 
                            const openvrml::field_value &value) 
            OPENVRML_THROW2(openvrml::unsupported_interface, std::bad_cast);
        virtual openvrml::event_listener &
        do_event_listener(const std::string & id)
            OPENVRML_THROW1(openvrml::unsupported_interface);
        virtual openvrml::event_emitter &
        do_event_emitter(const std::string & id)
            OPENVRML_THROW1(openvrml::unsupported_interface);
    };

    //
    // Since nothing should ever actually use the self_ref_node instance,
    // there's no need to go to the trouble to give it a valid node_type.
    //
    char not_remotely_a_node_type;
    self_ref_node::self_ref_node():
        node(reinterpret_cast<const openvrml::node_type &>(
                 not_remotely_a_node_type),
             boost::shared_ptr<openvrml::scope>())
    {}

    self_ref_node::~self_ref_node() OPENVRML_NOTHROW
    {}

    const openvrml::field_value &
    self_ref_node::do_field(const std::string &) const
        OPENVRML_THROW1(openvrml::unsupported_interface)
    {
        static const openvrml::sfbool val;
        return val;
    }

    void
    self_ref_node::do_assign_field(const std::string &id, 
                                   const openvrml::field_value &value) 
        OPENVRML_THROW1(openvrml::unsupported_interface)
    {
    }

    class OPENVRML_LOCAL dummy_listener : public openvrml::sfbool_listener {
    public:
        virtual ~dummy_listener() OPENVRML_NOTHROW
        {}

    private:
        virtual void do_process_event(const openvrml::sfbool &, double)
            OPENVRML_THROW1(std::bad_alloc)
        {}
    };

    openvrml::event_listener &
    self_ref_node::do_event_listener(const std::string &)
        OPENVRML_THROW1(openvrml::unsupported_interface)
    {
        static dummy_listener listener;
        return listener;
    }

    class OPENVRML_LOCAL dummy_emitter : public openvrml::sfbool_emitter {
    public:
        explicit dummy_emitter(const openvrml::sfbool & value):
            openvrml::event_emitter(value),
            openvrml::sfbool_emitter(value)
        {}

    private:
        virtual const std::string do_eventout_id() const OPENVRML_NOTHROW
        {
            return std::string();
        }            
    };

    openvrml::event_emitter &
    self_ref_node::do_event_emitter(const std::string &)
        OPENVRML_THROW1(openvrml::unsupported_interface)
    {
        openvrml::sfbool val;
        static dummy_emitter emitter(val);
        return emitter;
    }
}

/**
 * @brief Special value used when initializing a @c script_node.
 *
 * One should never attempt to dereference this value.  It is useful only for
 * comparison.
 */
const boost::intrusive_ptr<openvrml::node>
openvrml::node::self_tag(new self_ref_node);

/**
 * @internal
 *
 * @var boost::mutex openvrml::node::ref_count_mutex_
 *
 * @brief Mutex to guard @c #ref_count_.
 */

/**
 * @internal
 *
 * @var size_t openvrml::node::ref_count_
 *
 * @brief The number of owning references to the instance.
 */

/**
 * @internal
 *
 * @var const openvrml::node_type & openvrml::node::type_
 *
 * @brief The type information object for the @c node.
 */

/**
 * @internal
 *
 * @var boost::shared_ptr<openvrml::scope> openvrml::node::scope_
 *
 * @brief The @c scope to which the @c node belongs.
 *
 * @sa http://boost.org/libs/smart_ptr/shared_ptr.htm
 */

/**
 * @internal
 *
 * @var boost::shared_mutex openvrml::node::scene_mutex_
 *
 * @brief Mutex protecting @c #scene_.
 */

/**
 * @internal
 *
 * @var openvrml::scene * openvrml::node::scene_
 *
 * @brief The scene with which the @c node is associated.
 */

/**
 * @internal
 *
 * @var boost::shared_mutex openvrml::node::modified_mutex_
 *
 * @brief Mutex protecting @c #modified_.
 */

/**
 * @internal
 *
 * @var bool openvrml::node::modified_
 *
 * @brief Indicate whether the @c node has been modified.
 *
 * @sa #modified
 */

/**
 * @brief Construct.
 *
 * @param[in] type  the @c node_type associated with the instance.
 * @param[in] scope the @c scope associated with the instance.
 */
openvrml::node::node(const node_type & type,
                     const boost::shared_ptr<openvrml::scope> & scope)
    OPENVRML_NOTHROW:
    ref_count_(0),
    type_(type),
    scope_(scope),
    scene_(0),
    modified_(false)
{}

namespace {

    /**
     * @internal
     *
     * @brief Map of node names to node instances.
     */
    typedef std::map<std::string, openvrml::node *> named_node_map_t;

    struct OPENVRML_LOCAL node_is_ :
        std::unary_function<named_node_map_t::value_type, bool> {

        explicit node_is_(const openvrml::node & n):
            n(&n)
        {}

        bool operator()(const named_node_map_t::value_type & value) const
            OPENVRML_NOTHROW
        {
            return value.second == this->n;
        }

    private:
        const openvrml::node * n;
    };
}

/**
 * @brief Destructor.
 *
 * Remove @c node name (if any) from the @c scope.
 */
openvrml::node::~node() OPENVRML_NOTHROW
{
    //
    // If this is the primordial node in a prototype definition, this->scope_
    // will be null.
    //
    if (this->scope_) {
        using std::find_if;
        const named_node_map_t::iterator end =
            this->scope_->named_node_map.end();
        const named_node_map_t::iterator pos =
            find_if(this->scope_->named_node_map.begin(), end,
                    node_is_(*this));
        if (pos != end) { this->scope_->named_node_map.erase(pos); }
    }
}

/**
 * @brief Increment the reference count.
 *
 * Add an owning reference.
 */
void openvrml::node::add_ref() const OPENVRML_NOTHROW
{
    boost::mutex::scoped_lock lock(this->ref_count_mutex_);
    ++this->ref_count_;
}

/**
 * @fn void openvrml::intrusive_ptr_add_ref(const node * n)
 *
 * @relatesalso openvrml::node
 *
 * @brief Increment the reference count.
 *
 * This function is used by @c boost::intrusive_ptr<node>.
 *
 * @sa http://boost.org/libs/smart_ptr/intrusive_ptr.html
 */

/**
 * @fn void openvrml::node::remove_ref() const
 *
 * @brief Decrement the reference count.
 *
 * Remove an owning reference; <strong>but do not destroy the instance if the
 * reference count drops to zero</strong>.  This function should be used with
 * caution.  It is really only appropriate when the caller is aware that the
 * reference count may drop to zero but destroying the instance in that case
 * would be inappropriate.  In most cases it is appropriate to use
 * @c #release.
 */

/**
 * @brief Decrement the reference count; destroy the instance if the count
 *        drops to zero.
 */
void openvrml::node::release() const OPENVRML_NOTHROW
{
    bool delete_me;
    {
        boost::mutex::scoped_lock lock(this->ref_count_mutex_);
        delete_me = (--this->ref_count_ == 0);
    }
    if (delete_me) { delete this; }
}

/**
 * @fn void openvrml::intrusive_ptr_release(const node * n)
 *
 * @relatesalso openvrml::node
 *
 * @brief Decrement the reference count.
 *
 * This function is used by @c boost::intrusive_ptr<node>.
 *
 * @sa http://boost.org/libs/smart_ptr/intrusive_ptr.html
 */

/**
 * @brief The number of owning references to the instance.
 *
 * @return the number of owning references to the instance.
 */
size_t openvrml::node::use_count() const OPENVRML_NOTHROW
{
    return this->ref_count_;
}

/**
 * @brief The type information object for the @c node.
 *
 * @return the type information object for the @c node.
 */
const openvrml::node_type & openvrml::node::type() const OPENVRML_NOTHROW
{
    return this->type_;
}

/**
 * @brief Set the name of the @c node.
 *
 * @param[in] node_id the name for the @c node.
 *
 * @exception std::bad_alloc    if memory allocation fails.
 */
void openvrml::node::id(const std::string & node_id)
    OPENVRML_THROW1(std::bad_alloc)
{
    assert(this->scope_);
    this->scope_->named_node_map[node_id] = this; // Throws std::bad_alloc.
}

/**
 * @brief Retrieve the name of this @c node.
 *
 * @return the @c node name.
 */
const std::string & openvrml::node::id() const OPENVRML_NOTHROW
{
    using std::find_if;
    using std::string;

    assert(this->scope_);

    const named_node_map_t::iterator end = this->scope_->named_node_map.end();
    const named_node_map_t::iterator pos =
        find_if(this->scope_->named_node_map.begin(), end, node_is_(*this));
    static const string empty;
    return (pos != end) ? pos->first : empty;
}

/**
 * @fn const boost::shared_ptr<const openvrml::scope> & openvrml::node::scope() const
 *
 * @brief Get the @c scope to which the @c node belongs.
 *
 * @return the @c scope to which the @c node belongs.
 *
 * @sa http://boost.org/libs/smart_ptr/shared_ptr.htm
 */

/**
 * @brief Get the @c scene with which the @c node is associated.
 *
 * @return the @c scene with which the @c node is associated.
 */
openvrml::scene * openvrml::node::scene() const OPENVRML_NOTHROW
{
    using boost::shared_lock;
    using boost::shared_mutex;
    shared_lock<shared_mutex> lock(this->scene_mutex_);
    return this->scene_;
}

/**
 * @brief Get the implementation nodes of a @c PROTO instance.
 *
 * If the @c node is not a @c PROTO instance, the returned @c vector is empty.
 *
 * This function delegates to @c #do_impl_nodes.
 *
 * @return the implementation nodes.
 */
const std::vector<boost::intrusive_ptr<openvrml::node> > &
openvrml::node::impl_nodes() const OPENVRML_NOTHROW
{
    return this->do_impl_nodes();
}

/**
 * @brief Get the implementation nodes of a @c PROTO instance.
 *
 * This default implementation returns an empty @c vector.
 *
 * @return an empty @c vector.
 */
const std::vector<boost::intrusive_ptr<openvrml::node> > &
openvrml::node::do_impl_nodes() const OPENVRML_NOTHROW
{
    static const std::vector<boost::intrusive_ptr<openvrml::node> > empty_vec;
    return empty_vec;
}

/**
 * @brief Initialize the node.
 *
 * This method works recursively, initializing any child nodes to the same
 * @p scene and @p timestamp.  If the node has already been initialized, this
 * method has no effect.
 *
 * @param[in,out] scene the @c scene to which the @c node will belong.
 * @param[in] timestamp the current time.
 *
 * @exception std::bad_alloc    if memory allocation fails.
 *
 * @post @a #scene_ points to @p scene.
 */
void openvrml::node::initialize(openvrml::scene & scene,
                                const double timestamp)
    OPENVRML_THROW1(std::bad_alloc)
{
    using boost::upgrade_lock;
    using boost::shared_mutex;

    upgrade_lock<shared_mutex> lock(this->scene_mutex_);

    if (!this->scene_) {
        {
            boost::upgrade_to_unique_lock<shared_mutex> upgraded_lock(lock);
            this->scene_ = &scene;
        }
        this->do_initialize(timestamp);

        const node_interface_set & interfaces = this->type_.interfaces();
        for (node_interface_set::const_iterator interface_(interfaces.begin());
                interface_ != interfaces.end(); ++interface_) {
            if (interface_->type == node_interface::exposedfield_id
                    || interface_->type == node_interface::field_id) {
                if (interface_->field_type == field_value::sfnode_id) {
                    const sfnode & sfn = this->field<sfnode>(interface_->id);
                    if (sfn.value()) {
                        sfn.value()->initialize(scene, timestamp);
                    }
                } else if (interface_->field_type == field_value::mfnode_id) {
                    const mfnode & mfn = this->field<mfnode>(interface_->id);
                    for (size_t i = 0; i < mfn.value().size(); ++i) {
                        if (mfn.value()[i]) {
                            mfn.value()[i]->initialize(scene, timestamp);
                        }
                    }
                }
            }
        }
    }
    assert(this->scene_ == &scene);
}

/**
 * @brief Generalized field accessor.
 *
 * @param[in] id    the name of the field.
 *
 * @return the field value.
 *
 * @exception unsupported_interface if the node has no field named @p id.
 * @exception std::bad_alloc        if memory allocation fails.
 */
std::auto_ptr<openvrml::field_value>
openvrml::node::field(const std::string & id) const
    OPENVRML_THROW2(unsupported_interface, std::bad_alloc)
{
    return this->do_field(id).clone();
}

void
openvrml::node::assign_field(const std::string & id, const field_value &value ) 
    OPENVRML_THROW2(unsupported_interface, std::bad_cast)
{
    return this->do_assign_field(id, value);
}

/**
 * @fn const FieldValue & openvrml::node::field(const std::string & id) const
 *
 * @brief Generalized field accessor.
 *
 * @tparam FieldValue   a @link FieldValueConcept Field Value@endlink.
 *
 * @param[in] id    the name of the @c field.
 *
 * @return the field value.
 *
 * @exception unsupported_interface if the node has no field named @p id.
 * @exception std::bad_cast         if the node's @p id field is not a
 *                                  @p FieldValue.
 */

/**
 * @fn const openvrml::field_value & openvrml::node::do_field(const std::string & id) const
 *
 * @brief Called by @c node::field to get a @c field.
 *
 * @param[in] id    field identifier.
 *
 * @return the field value.
 *
 * @exception unsupported_interface if the @c node has no @c field @p id.
 */

/**
 * @brief Get an event listener.
 *
 * @param[in] id    an @c eventIn identifier.
 *
 * @exception unsupported_interface if the @c node has no @c eventIn @p id.
 */
openvrml::event_listener &
openvrml::node::event_listener(const std::string & id)
    OPENVRML_THROW1(unsupported_interface)
{
    return this->do_event_listener(id);
}

/**
 * @fn openvrml::field_value_listener<FieldValue> & openvrml::node::event_listener(const std::string & id)
 *
 * @brief Get an event listener.
 *
 * @tparam FieldValue   a @link FieldValueConcept Field Value@endlink.
 *
 * @param[in] id    an @c eventIn identifier.
 *
 * @exception unsupported_interface if the @c node has no @c eventIn @p id.
 * @exception std::bad_cast         if the <code>node</code>'s @p id
 *                                  @c eventIn is not a @p FieldValue.
 */

/**
 * @brief Get an event emitter.
 *
 * @param[in] id    an @c eventOut identifier.
 *
 * @exception unsupported_interface if the node has no eventOut @p id.
 */
openvrml::event_emitter & openvrml::node::event_emitter(const std::string & id)
    OPENVRML_THROW1(unsupported_interface)
{
    return this->do_event_emitter(id);
}

/**
 * @fn openvrml::field_value_emitter<FieldValue> & openvrml::node::event_emitter(const std::string & id)
 *
 * @brief Get an event emitter.
 *
 * @tparam FieldValue   a @link FieldValueConcept Field Value@endlink.
 *
 * @param[in] id    an @c eventOut identifier.
 *
 * @exception unsupported_interface if the @c node has no @c eventOut @p id.
 * @exception std::bad_cast         if the <code>node</code>'s @p id
 *                                  @c eventOut is not a @p FieldValue.
 */

/**
 * @brief Shut down the node.
 *
 * This method works recursively, shutting down any child @c node%s.  If the
 * @c node has already been shut down, this method has no effect.
 *
 * @param[in] timestamp the current time.
 *
 * @post @a scene is 0.
 */
void openvrml::node::shutdown(const double timestamp) OPENVRML_NOTHROW
{
    using boost::upgrade_lock;
    using boost::shared_mutex;

    upgrade_lock<shared_mutex> lock(this->scene_mutex_);

    if (this->scene_) {
        this->do_shutdown(timestamp);
        {
            boost::upgrade_to_unique_lock<shared_mutex> upgraded_lock(lock);
            this->scene_ = 0;
        }

        const node_interface_set & interfaces = this->type_.interfaces();
        for (node_interface_set::const_iterator interface_(interfaces.begin());
                interface_ != interfaces.end(); ++interface_) {
            if (interface_->type == node_interface::exposedfield_id
                    || interface_->type == node_interface::field_id) {
                if (interface_->field_type == field_value::sfnode_id) {
                    const sfnode & sfn = this->field<sfnode>(interface_->id);
                    if (sfn.value()) { sfn.value()->shutdown(timestamp); }
                } else if (interface_->field_type == field_value::mfnode_id) {
                    const mfnode & mfn = this->field<mfnode>(interface_->id);
                    for (size_t i = 0; i < mfn.value().size(); ++i) {
                        if (mfn.value()[i]) {
                            mfn.value()[i]->shutdown(timestamp);
                        }
                    }
                }
            }
        }
    }
    assert(!this->scene_);
}

/**
 * @fn void openvrml::node::do_shutdown(double timestamp)
 *
 * @brief Called by node::shutdown.
 *
 * @param[in] timestamp the current time.
 */

/**
 * @internal
 *
 * @brief Cast to a @c script_node.
 *
 * Default implementation returns 0.
 *
 * @return 0
 */
openvrml::script_node * openvrml::node::to_script() OPENVRML_NOTHROW
{
    return 0;
}

/**
 * @internal
 *
 * @brief Cast to an @c appearance_node.
 *
 * Default implementation returns 0.
 *
 * @return 0
 */
openvrml::appearance_node * openvrml::node::to_appearance() OPENVRML_NOTHROW
{
    return 0;
}

/**
 * @internal
 *
 * @brief Cast to a @c background_node.
 *
 * Default implementation returns 0.
 *
 * @return 0
 */
openvrml::background_node * openvrml::node::to_background()
    OPENVRML_NOTHROW
{
    return 0;
}

/**
 * @internal
 *
 * @brief Cast to a @c bounded_volume_node.
 *
 * Default implementation returns 0.
 *
 * @return 0
 */
openvrml::bounded_volume_node * openvrml::node::to_bounded_volume()
    OPENVRML_NOTHROW
{
    return 0;
}

/**
 * @internal
 *
 * @brief Cast to a @c child_node.
 *
 * Default implementation returns 0.
 *
 * @return 0
 */
openvrml::child_node * openvrml::node::to_child() OPENVRML_NOTHROW
{
    return 0;
}

/**
 * @internal
 *
 * @brief Cast to a @c color_node.
 *
 * Default implementation returns 0.
 *
 * @return 0
 */
openvrml::color_node * openvrml::node::to_color() OPENVRML_NOTHROW
{
    return 0;
}

/**
 * @internal
 *
 * @brief Cast to a @c color_rgba_node.
 *
 * Default implementation returns 0.
 *
 * @return 0
 */
openvrml::color_rgba_node * openvrml::node::to_color_rgba() OPENVRML_NOTHROW
{
    return 0;
}

/**
 * @internal
 *
 * @brief Cast to a @c coordinate_node.
 *
 * Default implementation returns 0.
 *
 * @return 0
 */
openvrml::coordinate_node * openvrml::node::to_coordinate() OPENVRML_NOTHROW
{
    return 0;
}

/**
 * @internal
 *
 * @brief Cast to a font_style_node.
 *
 * Default implementation returns 0.
 *
 * @return 0
 */
openvrml::font_style_node * openvrml::node::to_font_style() OPENVRML_NOTHROW
{
    return 0;
}

/**
 * @internal
 *
 * @brief Cast to a geometry_node.
 *
 * Default implementation returns 0.
 *
 * @return 0
 */
openvrml::geometry_node * openvrml::node::to_geometry() OPENVRML_NOTHROW
{
    return 0;
}

/**
 * @internal
 *
 * @brief Cast to a @c grouping_node.
 *
 * Default implementation returns 0.
 *
 * @return 0
 */
openvrml::grouping_node * openvrml::node::to_grouping() OPENVRML_NOTHROW
{
    return 0;
}

/**
 * @internal
 *
 * @brief Cast to a @c light_node.
 *
 * Default implementation returns 0.
 *
 * @return 0
 */
openvrml::light_node * openvrml::node::to_light() OPENVRML_NOTHROW
{
    return 0;
}

/**
 * @internal
 *
 * @brief Cast to a @c material_node.
 *
 * Default implementation returns 0.
 *
 * @return 0
 */
openvrml::material_node * openvrml::node::to_material() OPENVRML_NOTHROW
{
    return 0;
}

/**
 * @internal
 *
 * @brief Cast to a @c navigation_info_node.
 *
 * Default implementation returns 0.
 *
 * @return 0.
 */
openvrml::navigation_info_node * openvrml::node::to_navigation_info()
    OPENVRML_NOTHROW
{
    return 0;
}

/**
 * @internal
 *
 * @brief Cast to a @c normal_node.
 *
 * Default implementation returns 0.
 *
 * @return 0
 */
openvrml::normal_node * openvrml::node::to_normal() OPENVRML_NOTHROW
{
    return 0;
}

/**
 * @internal
 *
 * @brief Cast to a @c pointing_device_sensor_node.
 *
 * Default implementation returns 0.
 *
 * @return 0
 */
openvrml::pointing_device_sensor_node *
openvrml::node::to_pointing_device_sensor() OPENVRML_NOTHROW
{
    return 0;
}

/**
 * @internal
 *
 * @brief Cast to a @c scoped_light_node.
 *
 * @return 0.
 */
openvrml::scoped_light_node * openvrml::node::to_scoped_light()
    OPENVRML_NOTHROW
{
    return 0;
}

/**
 * @internal
 *
 * @brief Cast to a @c sound_source_node.
 *
 * Default implementation returns 0.
 *
 * @return 0
 */
openvrml::sound_source_node * openvrml::node::to_sound_source()
    OPENVRML_NOTHROW
{
    return 0;
}

/**
 * @internal
 *
 * @brief Cast to a @c texture_node.
 *
 * Default implementation returns 0.
 *
 * @return 0
 */
openvrml::texture_node * openvrml::node::to_texture() OPENVRML_NOTHROW
{
    return 0;
}

/**
 * @internal
 *
 * @brief Cast to a @c texture_coordinate_node.
 *
 * Default implementation returns 0.
 *
 * @return 0
 */
openvrml::texture_coordinate_node *
openvrml::node::to_texture_coordinate() OPENVRML_NOTHROW
{
    return 0;
}

/**
 * @internal
 *
 * @brief Cast to a @c texture_transform_node.
 *
 * Default implementation returns 0.
 *
 * @return 0
 */
openvrml::texture_transform_node *
openvrml::node::to_texture_transform() OPENVRML_NOTHROW
{
    return 0;
}

/**
 * @internal
 *
 * @brief Cast to a @c time_dependent_node.
 *
 * Default implementation returns 0.
 *
 * @return 0
 */
openvrml::time_dependent_node * openvrml::node::to_time_dependent()
    OPENVRML_NOTHROW
{
    return 0;
}

/**
 * @internal
 *
 * @brief Cast to a @c transform_node.
 *
 * Default implementation returns 0.
 *
 * @return 0
 */
openvrml::transform_node * openvrml::node::to_transform() OPENVRML_NOTHROW
{
    return 0;
}

/**
 * @internal
 *
 * @brief Cast to a @c viewpoint_node.
 *
 * Default implementation returns 0.
 *
 * @return 0
 */
openvrml::viewpoint_node * openvrml::node::to_viewpoint() OPENVRML_NOTHROW
{
    return 0;
}

/**
 * @brief Set the modified flag.
 *
 * Indicates the node needs to be revisited for rendering.
 *
 * @param[in] value
 *
 * @exception boost::thread_resource_error if @c #modified_mutex_ cannot be
 *                                         locked.
 */
void openvrml::node::modified(const bool value)
    OPENVRML_THROW1(boost::thread_resource_error)
{
    using boost::unique_lock;
    using boost::shared_mutex;
    unique_lock<shared_mutex> lock(this->modified_mutex_);
    this->modified_ = value;
    if (this->modified_) { this->type_.metatype().browser().modified(true); }
}

/**
 * @brief Determine whether the @c node has been modified.
 *
 * The default implementation returns whether this @c node has been modified.
 * Subclasses that can have child @c node%s should override this method and
 * return @c true if any of their children have been modified.
 *
 * @return @c true if the @c node has been modified; @c false otherwise.
 *
 * @exception boost::thread_resource_error if @c #modified_mutex_ cannot be
 *                                         locked.
 */
bool openvrml::node::modified() const
    OPENVRML_THROW1(boost::thread_resource_error)
{
    using boost::shared_lock;
    using boost::shared_mutex;
    shared_lock<shared_mutex> lock(this->modified_mutex_);
    return this->modified_ || this->do_modified();
}

/**
 * @brief Determine whether the @c node has been modified.
 *
 * The default implementation returns @c false.  Subclasses that can have
 * child @c node%s should override this method and return @c true if any of
 * their children has been modified.
 *
 * @return @c false.
 *
 * @exception boost::thread_resource_error if a mutex cannot be locked.
 */
bool openvrml::node::do_modified() const
    OPENVRML_THROW1(boost::thread_resource_error)
{
    return false;
}

/**
 * @brief Emit an event.
 *
 * @param[in,out] emitter   an @c event_emitter.
 * @param[in]     timestamp the current time.
 *
 * @exception std::bad_alloc    if memory allocation fails.
 */
void openvrml::node::emit_event(openvrml::event_emitter & emitter,
                                const double timestamp)
    OPENVRML_THROW1(std::bad_alloc)
{
    emitter.emit_event(timestamp);
}

/**
 * @brief The @c scene mutex.
 *
 * @return the @c scene mutex.
 */
boost::shared_mutex & openvrml::node::scene_mutex()
{
    return this->scene_mutex_;
}

namespace {
    struct OPENVRML_LOCAL field_printer_ {
        field_printer_(const openvrml::node & node,
                       openvrml::field_value::type_id type,
                       const std::string & interface_id,
                       std::ostream & out):
            node_(&node),
            type_(type),
            interface_id_(&interface_id),
            out_(&out)
        {}

        template <typename T>
        void operator()(T) const
        {
            if (T::field_value_type_id == this->type_) {
                (*this->out_) << this->node_->field<T>(*this->interface_id_);
            }
        }

    private:
        const openvrml::node * node_;
        openvrml::field_value::type_id type_;
        const std::string * interface_id_;
        std::ostream * out_;
    };

    const short indent_increment_ = 4;

    struct OPENVRML_LOCAL print_field_ :
        std::unary_function<openvrml::node_interface, void> {

        print_field_(const openvrml::node & n,
                     std::ostream & out,
                     const size_t indent):
            n(n),
            out(out),
            indent(indent)
        {}

        void operator()(const openvrml::node_interface & interface_) const
        {
            using namespace openvrml;
            using boost::mpl::for_each;
            using openvrml::local::field_value_types;
            if (interface_.type == node_interface::exposedfield_id
                    || interface_.type == node_interface::field_id) {
                this->out << std::string(this->indent + indent_increment_, ' ')
                          << interface_.id << ' ';
                for_each<field_value_types>(
                    field_printer_(n,
                                   interface_.field_type,
                                   interface_.id,
                                   this->out));
            }
        }

    private:
        const openvrml::node & n;
        std::ostream & out;
        const size_t indent;
    };
}

/**
 * @brief Pretty print.
 *
 * @param[in,out] out   output stream.
 * @param[in] indent    number of spaces per indentation level.
 *
 * @return @p out.
 */
std::ostream & openvrml::node::print(std::ostream & out,
                                     const size_t indent) const
{
    for (size_t i = 0; i < indent; ++i) { out << ' '; }
    std::string nodeId = this->id();
    if (!nodeId.empty()) { out << "DEF " << nodeId << " "; }
    out << this->type_.id() << " { ";
    const node_interface_set & interfaces = this->type_.interfaces();
    std::for_each(interfaces.begin(), interfaces.end(),
                  print_field_(*this, out, indent));
    return out << " }";
}

/**
 * @brief Stream output.
 *
 * @param[in,out] out   output stream.
 * @param[in]     n     a @c node.
 *
 * @return @p out.
 */
std::ostream & openvrml::operator<<(std::ostream & out, const node & n)
{
    return n.print(out, 0);
}

/**
 * @brief @c node subclass-specific initialization.
 *
 * This method is called by @c #initialize.  Subclasses of node should
 * override this method for any subclass-specific initialization.
 *
 * The default implementation of this method does nothing.
 *
 * @param[in] timestamp the current time.
 *
 * @exception std::bad_alloc    if memory allocation fails.
 */
void openvrml::node::do_initialize(double)
    OPENVRML_THROW1(std::bad_alloc)
{}

/**
 * @fn openvrml::event_listener & openvrml::node::do_event_listener(const std::string & id)
 *
 * @brief Get an event listener.
 *
 * This method is called by @c #event_listener.  Subclasses must implement
 * this method.
 *
 * @param[in] id    @c eventIn identifier.
 *
 * @return the event listener.
 *
 * @exception unsupported_interface if the node has no @c eventIn @p id.
 */

/**
 * @fn openvrml::event_emitter & openvrml::node::do_event_emitter(const std::string & id)
 *
 * @brief Get an event emitter.
 *
 * This method is called by @c #event_emitter.  Subclasses must implement this
 * method.
 *
 * @param[in] id    @c eventOut identifier.
 *
 * @return the event emitter.
 *
 * @exception unsupported_interface if the node has no @c eventOut @p id.
 */

/**
 * @brief @c node subclass-specific shut down.
 *
 * This method is called by @c #shutdown.  Subclasses of node should override
 * this method for any subclass-specific shut down.  Note that this method
 * cannot throw.
 *
 * The default implementation of this method does nothing.
 *
 * @param[in] timestamp the current time.
 */
void openvrml::node::do_shutdown(double) OPENVRML_NOTHROW
{}

/**
 * @relatesalso openvrml::node
 *
 * @brief Check whether a @c node is a @c PROTO instance.
 *
 * @param[in] n a @c node.
 *
 * @return @c true if @p n is a @c PROTO instance; @c false otherwise.
 */
bool openvrml::is_proto_instance(const node & n)
{
    return !n.impl_nodes().empty();
}

namespace {
    struct OPENVRML_LOCAL add_listener {
        add_listener(openvrml::event_emitter & emitter,
                     openvrml::event_listener & listener,
                     bool & added_route):
            emitter_(&emitter),
            listener_(&listener),
            added_route_(&added_route)
        {}

        template <typename T>
        void operator()(T) const
        {
            if (T::field_value_type_id == this->emitter_->value().type()) {
                typedef openvrml::field_value_emitter<T> emitter_t;
                typedef openvrml::field_value_listener<T> listener_t;
                *this->added_route_ =
                    dynamic_cast<emitter_t &>(*this->emitter_).add(
                        dynamic_cast<listener_t &>(*this->listener_));
            }
        }

        openvrml::event_emitter * emitter_;
        openvrml::event_listener * listener_;
        bool * added_route_;
    };
}

/**
 * @brief Add a route from an @c eventOut of this node to an @c eventIn of
 *        another node.
 *
 * If the route being added already exists, this method has no effect.
 *
 * @param[in,out] from      source node.
 * @param[in]     eventout  an eventOut of @p from.
 * @param[in,out] to        destination node.
 * @param[in]     eventin   an eventIn of @p to.
 *
 * @return @c true if a route was successfully added; @c false otherwise (if
 *         the route already existed).
 *
 * @exception std::bad_alloc            if memory allocation fails.
 * @exception unsupported_interface     if @p from has no eventOut
 *                                      @p eventout; or if @p to has no
 *                                      eventIn @p eventin.
 * @exception field_value_type_mismatch if @p eventout and @p eventin have
 *                                      different field value types.
 *
 * @pre @p from and @p to are not null.
 */
bool openvrml::add_route(node & from,
                         const std::string & eventout,
                         node & to,
                         const std::string & eventin)
    OPENVRML_THROW3(std::bad_alloc, unsupported_interface,
                    field_value_type_mismatch)
{
    using std::bad_cast;

    event_emitter & emitter = from.event_emitter(eventout);
    event_listener & listener = to.event_listener(eventin);
    bool added_route = false;
    try {
        using boost::mpl::for_each;
        using openvrml::local::field_value_types;
        for_each<field_value_types>(add_listener(emitter,
                                                 listener,
                                                 added_route));
    } catch (const bad_cast &) {
        throw field_value_type_mismatch();
    }
    return added_route;
}

namespace {
    struct OPENVRML_LOCAL remove_listener {
        remove_listener(openvrml::event_emitter & emitter,
                        openvrml::event_listener & listener,
                        bool & deleted_route):
            emitter_(&emitter),
            listener_(&listener),
            deleted_route_(&deleted_route)
        {}

        template <typename T>
        void operator()(T) const
        {
            if (T::field_value_type_id == this->emitter_->value().type()) {
                typedef openvrml::field_value_emitter<T> emitter_t;
                typedef openvrml::field_value_listener<T> listener_t;
                *this->deleted_route_ =
                    dynamic_cast<emitter_t &>(*this->emitter_).remove(
                        dynamic_cast<listener_t &>(*this->listener_));
            }
        }

        openvrml::event_emitter * emitter_;
        openvrml::event_listener * listener_;
        bool * deleted_route_;
    };
}

/**
 * @brief Remove a route from an @c eventOut from a @c node to an @c eventIn
 *        of another @c node.
 *
 * @param[in,out] from      source @c node.
 * @param[in]     eventout  an @c eventOut of @p from.
 * @param[in,out] to        destination @c node.
 * @param[in]     eventin   an @c eventIn of @p to.
 *
 * @return @c true if a route was deleted; @c false otherwise (if no such route
 *         existed).
 *
 * @exception unsupported_interface if @p from has no @c eventOut @p eventout
 *                                  or if @p to has no @c eventIn @p eventin.
 */
bool openvrml::delete_route(node & from,
                            const std::string & eventout,
                            node & to,
                            const std::string & eventin)
    OPENVRML_THROW1(unsupported_interface)
{
    using std::bad_cast;

    event_emitter & emitter = from.event_emitter(eventout);
    event_listener & listener = to.event_listener(eventin);
    bool deleted_route = false;
    try {
        using boost::mpl::for_each;
        using openvrml::local::field_value_types;
        for_each<field_value_types>(remove_listener(emitter,
                                                    listener,
                                                    deleted_route));
    } catch (const bad_cast &) {
        //
        // Do nothing.  If route removal fails, we simply return false.
        //
    }
    return deleted_route;
}


/**
 * @fn template <> openvrml::script_node * openvrml::node_cast<openvrml::script_node *>(node * n)
 *
 * @brief Cast to a @c script_node.
 *
 * @param[in] n node.
 *
 * @return a @c script_node pointer to the @c node pointed to by @p n, or 0 if
 *         the @c node is not a @c script_node.
 */

/**
 * @fn template <> openvrml::appearance_node * openvrml::node_cast<openvrml::appearance_node *>(node * n)
 *
 * @brief Cast to an @c appearance_node.
 *
 * @param[in] n @c node.
 *
 * @return an @c appearance_node pointer to the @c node pointed to by @p n, or
 *         0 if the @c node is not an @c appearance_node.
 */

/**
 * @fn template <> openvrml::child_node * openvrml::node_cast<openvrml::child_node *>(node * n)
 *
 * @brief Cast to a @c child_node.
 *
 * @param[in] n @c node.
 *
 * @return a @c child_node pointer to the @c node pointed to by @p n, or 0 if
 *         the @c node is not a @c child_node.
 */

/**
 * @fn template <> openvrml::color_node * openvrml::node_cast<openvrml::color_node *>(node * n)
 *
 * @brief Cast to a @c color_node.
 *
 * @param[in] n @c node.
 *
 * @return a @c color_node pointer to the @c node pointed to by @p n, or 0 if
 *         the @c node is not a @c color_node.
 */

/**
 * @fn template <> openvrml::color_rgba_node * openvrml::node_cast<openvrml::color_rgba_node *>(node * n)
 *
 * @brief Cast to a @c color_rgba_node.
 *
 * @param[in] n node.
 *
 * @return a @c color_rgba_node pointer to the node pointed to by @p n, or 0 if the
 *         node is not a @c color_rgba_node.
 */

/**
 * @fn template <> openvrml::coordinate_node * openvrml::node_cast<openvrml::coordinate_node *>(node * n)
 *
 * @brief Cast to a @c coordinate_node.
 *
 * @param[in] n @c node.
 *
 * @return a @c coordinate_node pointer to the @c node pointed to by @p n, or
 *         0 if the node is not a @c coordinate_node.
 */

/**
 * @fn template <> openvrml::font_style_node * openvrml::node_cast<openvrml::font_style_node *>(node * n)
 *
 * @brief Cast to a @c font_style_node.
 *
 * @param[in] n @c node.
 *
 * @return a @c font_style_node pointer to the @c node pointed to by @p n, or
 *         0 if the @c node is not a @c font_style_node.
 */

/**
 * @fn template <> openvrml::geometry_node * openvrml::node_cast<openvrml::geometry_node *>(node * n)
 *
 * @brief Cast to a @c geometry_node.
 *
 * @param[in] n @c node.
 *
 * @return a @c geometry_node pointer to the @c node pointed to by @p n, or 0
 *         if the @c node is not a @c geometry_node.
 */

/**
 * @fn template <> openvrml::grouping_node * openvrml::node_cast<openvrml::grouping_node *>(node * n)
 *
 * @brief Cast to a @c grouping_node.
 *
 * @param[in] n @c node.
 *
 * @return a @c grouping_node pointer to the @c node pointed to by @p n, or 0 if
 *         the @c node is not a @c grouping_node.
 */

/**
 * @fn template <> openvrml::material_node * openvrml::node_cast<openvrml::material_node *>(node * n)
 *
 * @brief Cast to a @c material_node.
 *
 * @param[in] n @c node.
 *
 * @return a @c material_node pointer to the @c node pointed to by @p n, or 0
 *         if the @c node is not a @c material_node.
 */

/**
 * @fn template <> openvrml::normal_node * openvrml::node_cast<openvrml::normal_node *>(node * n)
 *
 * @brief Cast to a @c normal_node.
 *
 * @param[in] n @c node.
 *
 * @return a @c normal_node pointer to the @c node pointed to by @p n, or 0 if
 *         the @c node is not a @c normal_node.
 */

/**
 * @fn template <> openvrml::sound_source_node * openvrml::node_cast<openvrml::sound_source_node *>(node * n)
 *
 * @brief Cast to a @c sound_source_node.
 *
 * @param[in] n @c node.
 *
 * @return a @c sound_source_node pointer to the @c node pointed to by @p n, or 0 if
 *         the @c node is not a @c sound_source_node.
 */

/**
 * @fn template <> openvrml::texture_node * openvrml::node_cast<openvrml::texture_node *>(node * n)
 *
 * @brief Cast to a @c texture_node.
 *
 * @param[in] n @c node.
 *
 * @return a @c texture_node pointer to the @c node pointed to by @p n, or 0
 *         if the @c node is not a @c texture_node.
 */

/**
 * @fn template <> openvrml::texture_coordinate_node * openvrml::node_cast<openvrml::texture_coordinate_node *>(node * n)
 *
 * @brief Cast to a @c texture_coordinate_node.
 *
 * @param[in] n @c node.
 *
 * @return a @c texture_coordinate_node pointer to the @c node pointed to by
 *         @p n, or 0 if the @c node is not a @c texture_coordinate_node.
 */

/**
 * @fn template <> openvrml::texture_transform_node * openvrml::node_cast<openvrml::texture_transform_node *>(node * n)
 *
 * @brief Cast to a @c texture_transform_node.
 *
 * @param[in] n @c node.
 *
 * @return a @c texture_transform_node pointer to the @c node pointed to by
 *         @p n, or 0 if the @c node is not a @c texture_transform_node.
 */

/**
 * @fn template <> openvrml::transform_node * openvrml::node_cast<openvrml::transform_node *>(node * n)
 *
 * @brief Cast to a transform_node.
 *
 * @param[in] n @c node.
 *
 * @return a @c transform_node pointer to the @c node pointed to by @p n, or 0
 *         if the @c node is not a @c transform_node.
 */

/**
 * @fn template <> openvrml::viewpoint_node * openvrml::node_cast<openvrml::viewpoint_node *>(node * n)
 *
 * @brief Cast to a @c viewpoint_node.
 *
 * @param[in] n @c node.
 *
 * @return a @c viewpoint_node pointer to the @c node pointed to by @p n, or 0
 *         if the @c node is not a @c viewpoint_node.
 */


/**
 * @class openvrml::appearance_node openvrml/node.h
 *
 * @brief Abstract base class for appearance nodes.
 */

/**
 * @brief Construct.
 *
 * @param[in] type  the @c node_type associated with the @c node.
 * @param[in] scope the @c scope the @c node belongs to.
 */
openvrml::appearance_node::
appearance_node(const node_type & type,
                const boost::shared_ptr<openvrml::scope> & scope)
    OPENVRML_NOTHROW:
    node(type, scope)
{}

/**
 * @brief Destroy.
 */
openvrml::appearance_node::~appearance_node() OPENVRML_NOTHROW
{}

/**
 * @brief Insert appearance when rendering.
 *
 * @param[in,out] v         @c viewer.
 * @param[in]     context   @c rendering_context.
 */
void openvrml::appearance_node::render_appearance(viewer & v,
                                                  rendering_context context)
{
    using boost::shared_lock;
    using boost::shared_mutex;
    shared_lock<shared_mutex> lock(this->scene_mutex());
    if (this->scene()) {
        this->do_render_appearance(v, context);
        this->modified(false);
    }
}

/**
 * @brief @c #render_appearance implementation.
 *
 * @param[in,out] v         @c viewer.
 * @param[in]     context   @c rendering_context.
 */
void
openvrml::appearance_node::do_render_appearance(viewer &, rendering_context)
{}

/**
 * @brief Cast to an @c appearance_node.
 *
 * @return a pointer to this @c appearance_node.
 */
openvrml::appearance_node * openvrml::appearance_node::to_appearance()
    OPENVRML_NOTHROW
{
    return this;
}

/**
 * @brief Get the material node associated with this appearance node.
 *
 * @return the @c material_node associated with this @c appearance_node.
 */
const boost::intrusive_ptr<openvrml::node> &
openvrml::appearance_node::material() const OPENVRML_NOTHROW
{
    return this->do_material();
}

/**
 * @fn const boost::intrusive_ptr<openvrml::node> & openvrml::appearance_node::do_material() const
 *
 * @brief Get the material node associated with this appearance node.
 *
 * @return the @c material_node associated with this @c appearance_node.
 */

/**
 * @brief Get the texture node associated with this appearance node.
 *
 * @return the @c texture_node associated with this @c appearance_node.
 */
const boost::intrusive_ptr<openvrml::node> &
openvrml::appearance_node::texture() const OPENVRML_NOTHROW
{
    return this->do_texture();
}

/**
 * @fn const boost::intrusive_ptr<openvrml::node> & openvrml::appearance_node::do_texture() const
 *
 * @brief Get the texture node associated with this appearance node.
 *
 * @return the @c texture_node associated with this @c appearance_node.
 */

/**
 * @brief Get the texture transform node associated with this appearance node.
 *
 * @return the @c texture_transform_node associated with this
 *         @c appearance_node.
 */
const boost::intrusive_ptr<openvrml::node> &
openvrml::appearance_node::texture_transform() const OPENVRML_NOTHROW
{
    return this->do_texture_transform();
}

/**
 * @fn const boost::intrusive_ptr<openvrml::node> & openvrml::appearance_node::do_texture_transform() const
 *
 * @brief Get the texture transform node associated with this appearance node.
 *
 * @return the @c texture_transform_node associated with this
 *         @c appearance_node.
 */


/**
 * @class openvrml::bounded_volume_node openvrml/node.h
 *
 * @brief Abstract base class for nodes that represent a bounded volume in the
 *        scene graph.
 */

/**
 * @internal
 *
 * @var boost::shared_mutex openvrml::bounded_volume_node::bounding_volume_dirty_mutex_
 *
 * @brief Mutex protecting @c #bounding_volume_dirty_.
 */

/**
 * @internal
 *
 * @var bool openvrml::bounded_volume_node::bounding_volume_dirty_
 *
 * @brief Indicate whether the <code>node</code>'s cached bounding volume
 *        needs updating.
 */

/**
 * @brief Construct.
 *
 * @param[in] type  the @c node_type associated with the node.
 * @param[in] scope the @c scope the node belongs to.
 */
openvrml::bounded_volume_node::
bounded_volume_node(const node_type & type,
                    const boost::shared_ptr<openvrml::scope> & scope)
    OPENVRML_NOTHROW:
    node(type, scope),
    bounding_volume_dirty_(false)
{}

/**
 * @brief Destroy.
 */
openvrml::bounded_volume_node::~bounded_volume_node() OPENVRML_NOTHROW
{}

/**
 * @brief Get this node's bounding volume.
 *
 * Nodes that have no bounding volume, or have a difficult to calculate
 * bvolume (like, say, Extrusion or Billboard) can just return an infinite
 * bsphere.  Note that returning an infinite bvolume means that all the node's
 * ancestors will also end up with an infinite bvolume, and will never be
 * culled.
 *
 * Delegates to @c #do_bounding_volume.
 *
 * @return a maximized bounding volume.
 */
const openvrml::bounding_volume &
openvrml::bounded_volume_node::bounding_volume() const
{
    using boost::unique_lock;
    using boost::shared_mutex;
    const openvrml::bounding_volume & bv = this->do_bounding_volume();
    unique_lock<shared_mutex> lock(this->bounding_volume_dirty_mutex_);
    this->bounding_volume_dirty_ = false;
    return bv;
}

/**
 * @brief Called by @c #bounding_volume.
 *
 * @return a maximized bounding volume.
 */
const openvrml::bounding_volume &
openvrml::bounded_volume_node::do_bounding_volume() const
{
    class default_bounding_volume : public bounding_sphere {
    public:
        default_bounding_volume()
        {
        }
    };

    static const default_bounding_volume default_bvolume;
    return default_bvolume;
}

/**
 * @brief Set whether the node's bounding volume needs to be recalculated.
 *
 * Indicate that a node's bounding volume needs to be recalculated (or not).
 * If a node's bounding volume is invalid, then the bounding volumes of all
 * that node's ancestors are also invalid. Normally, the node itself will
 * determine when its bounding volume needs updating.
 *
 * @param[in] value @c true if the node's bounding volume should be
 *                  recalculated; @c false otherwise.
 */
void openvrml::bounded_volume_node::bounding_volume_dirty(const bool value)
{
    using boost::unique_lock;
    using boost::shared_mutex;
    unique_lock<shared_mutex> lock(this->bounding_volume_dirty_mutex_);
    this->bounding_volume_dirty_ = value;
    if (value) { // only if dirtying, not clearing
        this->type().metatype().browser().flags_need_updating = true;
    }
}

/**
 * @brief Whether the node's bounding volume needs to be recalculated.
 *
 * @return @c true if the node's bounding volume needs to be recalculated;
 *         @c false otherwise.
 */
bool openvrml::bounded_volume_node::bounding_volume_dirty() const
{
    using boost::shared_lock;
    using boost::shared_mutex;
    shared_lock<shared_mutex> lock(this->bounding_volume_dirty_mutex_);
    if (this->type().metatype().browser().flags_need_updating) {
        this->type().metatype().browser().update_flags();
        this->type().metatype().browser().flags_need_updating = false;
    }
    return this->bounding_volume_dirty_;
}

/**
 * @brief Cast to an @c bounded_volume_node.
 *
 * @return a pointer to this @c bounded_volume_node.
 */
openvrml::bounded_volume_node *
openvrml::bounded_volume_node::to_bounded_volume() OPENVRML_NOTHROW
{
    return this;
}


/**
 * @class openvrml::child_node openvrml/node.h
 *
 * @brief Abstract base class for child nodes.
 */

/**
 * @brief Constructor.
 *
 * @param[in] type  the @c node_type associated with the node.
 * @param[in] scope the @c scope the node belongs to.
 */
openvrml::child_node::
child_node(const node_type & type,
           const boost::shared_ptr<openvrml::scope> & scope)
    OPENVRML_NOTHROW:
    node(type, scope),
    bounded_volume_node(type, scope)
{}

/**
 * @brief Destructor.
 */
openvrml::child_node::~child_node() OPENVRML_NOTHROW
{}

/**
 * @brief Called when the node is relocated to a new position in the scene
 *      graph.
 *
 * This function delegates to the virtual function @c #do_relocate. @c relocate
 * should be called by eventIn handlers that receive nodes.
 *
 * @exception std::bad_alloc    if memory allocation fails.
 */
void openvrml::child_node::relocate() OPENVRML_THROW1(std::bad_alloc)
{
    typedef void (child_node::* Do_relocate)();

    class RelocateTraverser : public node_traverser {
        Do_relocate do_relocate;

    public:
        explicit RelocateTraverser(const Do_relocate do_relocate)
            OPENVRML_NOTHROW:
            do_relocate(do_relocate)
        {}

        virtual ~RelocateTraverser() OPENVRML_NOTHROW
        {}

    private:
        virtual void on_entering(node & n) OPENVRML_THROW1(std::bad_alloc)
        {
            child_node * const child = node_cast<child_node *>(&n);
            if (child) { (child->*this->do_relocate)(); }
        }
    };

    Do_relocate do_reloc = &child_node::do_relocate;

    RelocateTraverser(do_reloc).traverse(*this);
}

/**
 * @brief Render the node.
 *
 * This function delegates to @c #do_render_child.
 *
 * @param[in,out] v         viewer implementation responsible for actually
 *                          doing the drawing.
 * @param[in]     context   generic context argument; holds things like the
 *                          accumulated modelview transform.
 */
void openvrml::child_node::render_child(viewer & v,
                                        const rendering_context context)
{
    using boost::shared_lock;
    using boost::shared_mutex;
    shared_lock<shared_mutex> lock(this->scene_mutex());
    if (this->scene()) {
        this->do_render_child(v, context);

        if (context.draw_bounding_spheres && 
            this == dynamic_cast<const openvrml::node*>(
                context.bounding_sphere_target
            ) 
        ) {
            using boost::polymorphic_downcast;
            const openvrml::bounding_sphere *bs =
                polymorphic_downcast<const openvrml::bounding_sphere *>(
                    &this->bounding_volume()
                );
            if( bs != NULL )
                v.draw_bounding_sphere(*bs, context.cull_flag);
        }

        this->modified(false);
    }
}

/**
 * @brief @c #render_child implementation.
 *
 * Rendered @c child_node%s should override this method.
 *
 * @param[in,out] v         viewer implementation responsible for actually
 *                          doing the drawing.
 * @param[in]     context   generic context argument; holds things like the
 *                          accumulated modelview transform.
 */
void openvrml::child_node::do_render_child(viewer &, rendering_context)
{}

/**
 * @brief Cast to a @c child_node.
 *
 * @return a pointer to this @c child_node.
 */
openvrml::child_node * openvrml::child_node::to_child() OPENVRML_NOTHROW
{
    return this;
}

/**
 * @brief @c child_node subclass-specific relocation update.
 *
 * This method is called by @c #relocate.  Subclasses of @c child_node should
 * override this function for any subclass-specific updates that need to be
 * performed following relocation of a @c child_node to a new position in the
 * scene graph (for example, updating a @c node_path).
 *
 * The default implementation of this method does nothing.
 */
void openvrml::child_node::do_relocate() OPENVRML_THROW1(std::bad_alloc)
{}


/**
 * @class openvrml::background_node openvrml/node.h
 *
 * @brief Abstract base class for background nodes.
 */

/**
 * @brief Construct.
 *
 * @param[in] type  the @c node_type associated with the node.
 * @param[in] scope the scope the node belongs to.
 */
openvrml::background_node::
background_node(const node_type & type,
                const boost::shared_ptr<openvrml::scope> & scope)
    OPENVRML_NOTHROW:
    node(type, scope),
    bounded_volume_node(type, scope),
    child_node(type, scope)
{}

/**
 * @brief Destroy.
 */
openvrml::background_node::~background_node() OPENVRML_NOTHROW
{}

/**
 * @brief Cast to a @c background_node.
 *
 * @return a pointer to this @c background_node.
 */
openvrml::background_node * openvrml::background_node::to_background()
    OPENVRML_NOTHROW
{
    return this;
}

/**
 * @brief Ground angles.
 *
 * This function delegates to @c #do_ground_angle.
 *
 * @return a vector of angles corresponding to ground colors.
 */
const std::vector<float> &
openvrml::background_node::ground_angle() const OPENVRML_NOTHROW
{
    return this->do_ground_angle();
}

/**
 * @fn const std::vector<float> & openvrml::background_node::do_ground_angle() const
 *
 * @brief Ground angles.
 *
 * @return a vector of angles corresponding to ground colors.
 */

/**
 * @brief Ground colors.
 *
 * This function delegates to @c #do_ground_color.
 *
 * @return a vector of ground colors.
 */
const std::vector<openvrml::color> &
openvrml::background_node::ground_color() const OPENVRML_NOTHROW
{
    return this->do_ground_color();
}

/**
 * @fn const std::vector<openvrml::color> & openvrml::background_node::do_ground_color() const
 *
 * @brief Ground colors.
 *
 * @return a vector of ground colors.
 */

/**
 * @brief Sky angles.
 *
 * This function delegates to @c #do_sky_angle.
 *
 * @return a vector of angles corresponding to sky colors.
 */
const std::vector<float> &
openvrml::background_node::sky_angle() const OPENVRML_NOTHROW
{
    return this->do_sky_angle();
}

/**
 * @fn const std::vector<float> & openvrml::background_node::do_sky_angle() const
 *
 * @brief Sky angles.
 *
 * @return a vector of angles corresponding to sky colors.
 */

/**
 * @brief Sky colors.
 *
 * This function delegates to @c #do_sky_color.
 *
 * @return a vector of sky colors.
 */
const std::vector<openvrml::color> &
openvrml::background_node::sky_color() const OPENVRML_NOTHROW
{
    return this->do_sky_color();
}

/**
 * @fn const std::vector<openvrml::color> & openvrml::background_node::do_sky_color() const
 *
 * @brief Sky colors.
 *
 * @return a vector of sky colors.
 */

/**
 * @brief Front texture.
 *
 * This function delegates to @c #do_front.
 *
 * @return the front texture.
 */
openvrml::texture_node * openvrml::background_node::front() const
    OPENVRML_NOTHROW
{
    return this->do_front();
}

/**
 * @fn openvrml::texture_node * openvrml::background_node::do_front() const
 *
 * @brief Front texture.
 *
 * @return the front texture.
 */

/**
 * @brief Back texture.
 *
 * This function delegates to @c #do_back.
 *
 * @return the back texture.
 */
openvrml::texture_node * openvrml::background_node::back() const
    OPENVRML_NOTHROW
{
    return this->do_back();
}

/**
 * @fn openvrml::texture_node * openvrml::background_node::do_back() const
 *
 * @brief Back texture.
 *
 * @return the back texture.
 */

/**
 * @brief Left texture.
 *
 * This function delegates to @c #do_left.
 *
 * @return the left texture.
 */
openvrml::texture_node * openvrml::background_node::left() const
    OPENVRML_NOTHROW
{
    return this->do_left();
}

/**
 * @fn openvrml::texture_node * openvrml::background_node::do_left() const
 *
 * @brief Left texture.
 *
 * @return the left texture.
 */

/**
 * @brief Right texture.
 *
 * This function delegates to @c #do_right.
 *
 * @return the right texture.
 */
openvrml::texture_node * openvrml::background_node::right() const
    OPENVRML_NOTHROW
{
    return this->do_right();
}

/**
 * @fn openvrml::texture_node * openvrml::background_node::do_right() const
 *
 * @brief Right texture.
 *
 * @return the right texture.
 */

/**
 * @brief Top texture.
 *
 * This function delegates to @c #do_top.
 *
 * @return the top texture.
 */
openvrml::texture_node * openvrml::background_node::top() const
    OPENVRML_NOTHROW
{
    return this->do_top();
}

/**
 * @fn openvrml::texture_node * openvrml::background_node::do_top() const
 *
 * @brief Top texture.
 *
 * @return the top texture.
 */

/**
 * @brief Bottom texture.
 *
 * This function delegates to @c #do_bottom.
 *
 * @return the bottom texture.
 */
openvrml::texture_node * openvrml::background_node::bottom() const
    OPENVRML_NOTHROW
{
    return this->do_bottom();
}

/**
 * @fn openvrml::texture_node * openvrml::background_node::do_bottom() const
 *
 * @brief Bottom texture.
 *
 * @return the bottom texture.
 */


/**
 * @class openvrml::color_node openvrml/node.h
 *
 * @brief Abstract base class for color nodes.
 */

/**
 * @brief Construct.
 *
 * @param[in] type  the @c node_type associated with the node.
 * @param[in] scope the scope the node belongs to.
 */
openvrml::color_node::
color_node(const node_type & type,
           const boost::shared_ptr<openvrml::scope> & scope)
    OPENVRML_NOTHROW:
    node(type, scope)
{}

/**
 * @brief Destroy.
 */
openvrml::color_node::~color_node() OPENVRML_NOTHROW
{}

/**
 * @brief Cast to a @c color_node.
 *
 * @return a pointer to this @c color_node.
 */
openvrml::color_node * openvrml::color_node::to_color() OPENVRML_NOTHROW
{
    return this;
}

/**
 * @brief Get the color array encapsulated by this node.
 *
 * This function delegates to @c #do_color.
 *
 * @return the color array for this node.
 */
const std::vector<openvrml::color> & openvrml::color_node::color() const
    OPENVRML_NOTHROW
{
    return this->do_color();
}

/**
 * @fn const std::vector<openvrml::color> & openvrml::color_node::do_color() const
 *
 * @brief Get the color array encapsulated by this node.
 *
 * @return the color array for this node.
 */


/**
 * @class openvrml::color_rgba_node openvrml/node.h
 *
 * @brief Abstract base class for RGBA color nodes.
 */

/**
 * @brief Construct.
 *
 * @param[in] type  the node_type associated with the node.
 * @param[in] scope the scope the node belongs to.
 */
openvrml::color_rgba_node::
color_rgba_node(const node_type & type,
                const boost::shared_ptr<openvrml::scope> & scope)
    OPENVRML_NOTHROW:
    node(type, scope)
{}

/**
 * @brief Destroy.
 */
openvrml::color_rgba_node::~color_rgba_node() OPENVRML_NOTHROW
{}

/**
 * @brief Cast to a @c color_rgba_node.
 *
 * @return a pointer to this @c color_rgba_node.
 */
openvrml::color_rgba_node *
openvrml::color_rgba_node::to_color_rgba() OPENVRML_NOTHROW
{
    return this;
}

/**
 * @brief Get the @c color_rgba array encapsulated by this @c node.
 *
 * This function delegates to @c #do_color_rgba.
 *
 * @return the @c color_rgba array for this @c node.
 */
const std::vector<openvrml::color_rgba> &
openvrml::color_rgba_node::color_rgba() const OPENVRML_NOTHROW
{
    return this->do_color_rgba();
}

/**
 * @fn const std::vector<openvrml::color_rgba> & openvrml::color_rgba_node::do_color_rgba() const
 *
 * @brief Get the @c color_rgba array encapsulated by this @c node.
 *
 * @return the @c color_rgba array for this @c node.
 */


/**
 * @class openvrml::coordinate_node openvrml/node.h
 *
 * @brief Abstract base class for coordinate nodes.
 */

/**
 * @brief Construct.
 *
 * @param[in] type  the @c node_type associated with the @c node.
 * @param[in] scope the @c scope the @c node belongs to.
 */
openvrml::coordinate_node::
coordinate_node(const node_type & type,
                const boost::shared_ptr<openvrml::scope> & scope)
    OPENVRML_NOTHROW:
    node(type, scope)
{}

/**
 * @brief Destroy.
 */
openvrml::coordinate_node::~coordinate_node() OPENVRML_NOTHROW
{}

/**
 * @brief Cast to a @c coordinate_node.
 *
 * @return a pointer to this @c coordinate_node.
 */
openvrml::coordinate_node * openvrml::coordinate_node::to_coordinate()
    OPENVRML_NOTHROW
{
    return this;
}

/**
 * @brief Get the points encapsulated by this node.
 *
 * This function delegates to @c #do_point.
 *
 * @return the array of points for this node.
 */
const std::vector<openvrml::vec3f> & openvrml::coordinate_node::point() const
    OPENVRML_NOTHROW
{
    return this->do_point();
}

/**
 * @fn const std::vector<openvrml::vec3f> & openvrml::coordinate_node::do_point() const
 *
 * @brief Get the points encapsulated by this node.
 *
 * @return the array of points for this node.
 */


/**
 * @class openvrml::font_style_node openvrml/node.h
 *
 * @brief Abstract base class for font style nodes.
 */

/**
 * @brief Construct.
 *
 * @param[in] type  the @c node_type associated with the node.
 * @param[in] scope the @c scope the node belongs to.
 */
openvrml::font_style_node::
font_style_node(const node_type & type,
                const boost::shared_ptr<openvrml::scope> & scope)
    OPENVRML_NOTHROW:
    node(type, scope)
{}

/**
 * @brief Destroy.
 */
openvrml::font_style_node::~font_style_node() OPENVRML_NOTHROW
{}

/**
 * @brief Cast to a @c font_style_node.
 *
 * @return a pointer to this @c font_style_node.
 */
openvrml::font_style_node * openvrml::font_style_node::to_font_style()
    OPENVRML_NOTHROW
{
    return this;
}

/**
 * @brief Get the list of font families.
 *
 * This function delegates to @c #do_family.
 *
 * @return the font families that may be used for this FontStyle.
 */
const std::vector<std::string> & openvrml::font_style_node::family() const
    OPENVRML_NOTHROW
{
    return this->do_family();
}

/**
 * @fn const std::vector<std::string> & openvrml::font_style_node::do_family() const
 *
 * @brief Get the list of font families.
 *
 * @return the font families that may be used for this FontStyle.
 */

/**
 * @brief Get the flag indicating whether the text should be horizontal or
 *      vertical.
 *
 * This function delegates to @c #do_horizontal.
 *
 * @return @c true if the text should be horizontal, or @c false if the text
 *      should be vertical.
 */
bool openvrml::font_style_node::horizontal() const OPENVRML_NOTHROW
{
    return this->do_horizontal();
}

/**
 * @fn bool openvrml::font_style_node::do_horizontal() const
 *
 * @brief Get the flag indicating whether the text should be horizontal or
 *      vertical.
 *
 * @return @c true if the text should be horizontal, or @c false if the text
 *      should be vertical.
 */

/**
 * @brief Get the descriptor for the text justification.
 *
 * This function delegates to @c #do_justify.
 *
 * @return the characteristics of the text justification.
 */
const std::vector<std::string> & openvrml::font_style_node::justify() const
    OPENVRML_NOTHROW
{
    return this->do_justify();
}

/**
 * @fn const std::vector<std::string> & openvrml::font_style_node::do_justify() const
 *
 * @brief Get the descriptor for the text justification.
 *
 * @return the characteristics of the text justification.
 */

/**
 * @brief Get the language code.
 *
 * This function delegates to @c #do_language.
 *
 * @return the language code.
 */
const std::string & openvrml::font_style_node::language() const OPENVRML_NOTHROW
{
    return this->do_language();
}

/**
 * @fn const std::string & openvrml::font_style_node::do_language() const
 *
 * @brief Get the language code.
 *
 * @return the language code.
 */

/**
 * @brief Get the flag indicating whether the text should be rendered
 *      left-to-right.
 *
 * This function delegates to @c #do_left_to_right.
 *
 * @return @c true if the text should be rendered left-to-right, or @c false if
 *      the text should be rendered right-to-left.
 */
bool openvrml::font_style_node::left_to_right() const OPENVRML_NOTHROW
{
    return this->do_left_to_right();
}

/**
 * @fn bool openvrml::font_style_node::do_left_to_right() const
 *
 * @brief Get the flag indicating whether the text should be rendered
 *      left-to-right.
 *
 * @return @c true if the text should be rendered left-to-right, or @c false if
 *      the text should be rendered right-to-left.
 */

/**
 * @brief Get the size of the text.
 *
 * This function delegates to @c #do_size.
 *
 * @return the size of the text.
 */
float openvrml::font_style_node::size() const OPENVRML_NOTHROW
{
    return this->do_size();
}

/**
 * @fn float openvrml::font_style_node::do_size() const
 *
 * @brief Get the size of the text.
 *
 * @return the size of the text.
 */

/**
 * @brief Get the spacing for the text.
 *
 * This function delegates to @c #do_spacing.
 *
 * @return the spacing for the text.
 */
float openvrml::font_style_node::spacing() const OPENVRML_NOTHROW
{
    return this->do_spacing();
}

/**
 * @fn float openvrml::font_style_node::do_spacing() const
 *
 * @brief Get the spacing for the text.
 *
 * @return the spacing for the text.
 */

/**
 * @brief Get the style for the text.
 *
 * This function delegates to @c #do_style.
 *
 * @return the text style.
 */
const std::string & openvrml::font_style_node::style() const OPENVRML_NOTHROW
{
    return this->do_style();
}

/**
 * @fn const std::string & openvrml::font_style_node::do_style() const
 *
 * @brief Get the style for the text.
 *
 * @return the text style.
 */

/**
 * @brief Get the flag indicating whether the text should be rendered
 *      top-to-bottom.
 *
 * This function delegates to @c #do_top_to_bottom.
 *
 * @return @c true if the text should be rendered top-to-bottom, or @c false if
 *      the text should be rendered bottom-to-top.
 */
bool openvrml::font_style_node::top_to_bottom() const OPENVRML_NOTHROW
{
    return this->do_top_to_bottom();
}

/**
 * @fn bool openvrml::font_style_node::do_top_to_bottom() const
 *
 * @brief Get the flag indicating whether the text should be rendered
 *      top-to-bottom.
 *
 * @return @c true if the text should be rendered top-to-bottom, or @c false if
 *      the text should be rendered bottom-to-top.
 */


/**
 * @class openvrml::geometry_node openvrml/node.h
 *
 * @brief Abstract base class for geometry nodes.
 */

/**
 * @brief Construct.
 *
 * @param[in] type  the @c node_type associated with the @c node.
 * @param[in] scope the @c scope the @c node belongs to.
 */
openvrml::geometry_node::
geometry_node(const node_type & type,
              const boost::shared_ptr<openvrml::scope> & scope)
    OPENVRML_NOTHROW:
    node(type, scope),
    bounded_volume_node(type, scope)
{}

/**
 * @brief Destroy.
 */
openvrml::geometry_node::~geometry_node() OPENVRML_NOTHROW
{}

/**
 * @brief Cast to a @c geometry_node.
 *
 * @return a pointer to this @c geometry_node.
 */
openvrml::geometry_node * openvrml::geometry_node::to_geometry()
    OPENVRML_NOTHROW
{
    return this;
}

/**
 * @brief Insert geometry into a viewer.
 *
 * @param[in,out] v     viewer.
 * @param[in] context   rendering context.
 */
void openvrml::geometry_node::render_geometry(viewer & v,
                                              rendering_context context)
{
    using boost::shared_lock;
    using boost::shared_mutex;
    shared_lock<shared_mutex> lock(this->scene_mutex());

    if (!this->scene()) { return; }

    if (this->modified()) { v.remove_object(*this); }

    this->do_render_geometry(v, context);
    this->modified(false);
}

/**
 * @brief Indicates whether the geometry should be drawn with the emissive
 *        color.
 *
 * @return @c true if the geometry should be drawn with the emissive color;
 *         @c false otherwise (if the geometry should be drawn with the diffuse
 *         color).
 */
bool openvrml::geometry_node::emissive() const OPENVRML_NOTHROW
{
    return this->do_emissive();
}

/**
 * @brief @c #render_geometry implementation.
 *
 * @param[in,out] v     viewer.
 * @param[in] context   rendering context.
 */
void openvrml::geometry_node::do_render_geometry(viewer &, rendering_context)
{}

/**
 * @brief @c #emissive implementation.
 *
 * @return @c false.
 */
bool openvrml::geometry_node::do_emissive() const OPENVRML_NOTHROW
{
    return false;
}

/**
 * @brief Get the color node (if any) associated with this geometry.
 *
 * @return the @c color_node associated associated with this geometry, or 0 if
 *      there is no such node.
 *
 * @todo Reevaluate the way the renderer visits geometry nodes; potentially
 *      eliminate this method.
 */
const openvrml::color_node * openvrml::geometry_node::color() const
    OPENVRML_NOTHROW
{
    return this->do_color();
}

/**
 * @brief Get the color node (if any) associated with this geometry.
 *
 * @return the @c color_node associated associated with this geometry, or 0 if
 *      there is no such node.
 */
const openvrml::color_node * openvrml::geometry_node::do_color() const
    OPENVRML_NOTHROW
{
    return 0;
}


/**
 * @class openvrml::grouping_node openvrml/node.h
 *
 * @brief Abstract base class for grouping nodes.
 */

/**
 * @brief Construct.
 *
 * @param[in] type  the @c node_type associated with the node.
 * @param[in] scope the @c scope the node belongs to.
 */
openvrml::grouping_node::
grouping_node(const node_type & type,
              const boost::shared_ptr<openvrml::scope> & scope)
    OPENVRML_NOTHROW:
    node(type, scope),
    bounded_volume_node(type, scope),
    child_node(type, scope)
{}

/**
 * @brief Destroy.
 */
openvrml::grouping_node::~grouping_node() OPENVRML_NOTHROW
{}

/**
 * @brief Cast to a @c grouping_node.
 *
 * @return a pointer to this @c grouping_node.
 */
openvrml::grouping_node * openvrml::grouping_node::to_grouping()
    OPENVRML_NOTHROW
{
    return this;
}

/**
 * @brief Get the children in the scene graph.
 *
 * This function delegates to @c #do_children.
 *
 * @return the children in the scene graph.
 *
 * @exception std::bad_alloc    if memory allocation fails.
 */
const std::vector<boost::intrusive_ptr<openvrml::node> >
openvrml::grouping_node::children() const OPENVRML_THROW1(std::bad_alloc)
{
    return this->do_children();
}

/**
 * @fn const std::vector<boost::intrusive_ptr<openvrml::node> > openvrml::grouping_node::do_children() const
 *
 * @brief Get the children in the scene graph.
 *
 * @return the child nodes in the scene graph.
 *
 * @exception std::bad_alloc    if memory allocation fails.
 */

/**
 * @brief Called in response to user interaction to activate any child pointing
 *        device sensor nodes.
 *
 * Calls @c pointing_device_sendor_node::activate for child
 * @c pointing_device_sensor_node%s, recursively.
 *
 * @param[in] timestamp the current time.
 * @param[in] over      whether the pointer is over sensitive geometry.
 * @param[in] active    whether the pointer has activated sensitive geometry.
 * @param[in] p         the activation point.
 */
void
openvrml::grouping_node::
activate_pointing_device_sensors(const double timestamp,
                                 const bool over,
                                 const bool active,
                                 const double (&p)[3])
{
    typedef std::vector<boost::intrusive_ptr<node> > children_t;
    const children_t & children(this->children());
    for (children_t::const_iterator child = children.begin();
         child != children.end();
         ++child) {
        if (pointing_device_sensor_node * pointing_device_sensor =
            node_cast<pointing_device_sensor_node *>(child->get())) {
            pointing_device_sensor->activate(timestamp, over, active, p);
        } else if (grouping_node * grouping =
                   node_cast<grouping_node *>(child->get())) {
            grouping->activate_pointing_device_sensors(timestamp,
                                                       over,
                                                       active,
                                                       p);
        }
    }
}


/**
 * @class openvrml::light_node openvrml/node.h
 *
 * @brief Abstract base class for light nodes.
 */

/**
 * @brief Construct.
 *
 * @param[in] type  the @c node_type associated with the node.
 * @param[in] scope the @c scope the node belongs to.
 */
openvrml::light_node::
light_node(const node_type & type,
           const boost::shared_ptr<openvrml::scope> & scope)
    OPENVRML_NOTHROW:
    node(type, scope),
    bounded_volume_node(type, scope),
    child_node(type, scope)
{}

/**
 * @brief Destroy.
 */
openvrml::light_node::~light_node() OPENVRML_NOTHROW
{}

/**
 * @brief Cast to a @c light_node.
 *
 * @return a pointer to this @c light_node.
 */
openvrml::light_node * openvrml::light_node::to_light() OPENVRML_NOTHROW
{
    return this;
}

/**
 * @brief Ambient intensity.
 *
 * Delegates to @c #do_ambient_intensity.
 *
 * @return the ambient intensity.
 */
float openvrml::light_node::ambient_intensity() const OPENVRML_NOTHROW
{
    return this->do_ambient_intensity();
}

/**
 * @fn float openvrml::light_node::do_ambient_intensity() const
 *
 * @brief @c #ambient_intensity implementation.
 *
 * @return the ambient intensity.
 */

/**
 * @brief Intensity.
 *
 * Delegates to @c #do_intensity.
 *
 * @return the intensity.
 */
float openvrml::light_node::intensity() const OPENVRML_NOTHROW
{
    return this->do_intensity();
}

/**
 * @fn float openvrml::light_node::do_intensity() const
 *
 * @brief @c #intensity implementation.
 *
 * @return the intensity.
 */

/**
 * @brief &ldquo;On&rdquo; state.
 *
 * Delegates to @c #do_on.
 *
 * @return @c true if the light is on; @c false otherwise.
 */
bool openvrml::light_node::on() const OPENVRML_NOTHROW
{
    return this->do_on();
}

/**
 * @fn bool openvrml::light_node::do_on() const
 *
 * @brief @c #on implementation.
 *
 * @return @c true if the light is on; @c false otherwise.
 */

/**
 * @brief Color.
 *
 * Delegates to @c #do_color.
 *
 * @return the color.
 */
const openvrml::color & openvrml::light_node::color() const OPENVRML_NOTHROW
{
    return this->do_color();
}

/**
 * @fn const openvrml::color & openvrml::light_node::do_color() const
 *
 * @brief @c #color implementation.
 *
 * @return the color.
 */


/**
 * @class openvrml::material_node openvrml/node.h
 *
 * @brief Abstract base class for material nodes.
 */

/**
 * @brief Construct.
 *
 * @param[in] type  the @c node_type associated with the node.
 * @param[in] scope the @c scope the node belongs to.
 */
openvrml::material_node::
material_node(const node_type & type,
              const boost::shared_ptr<openvrml::scope> & scope)
    OPENVRML_NOTHROW:
    node(type, scope)
{}

/**
 * @brief Destroy.
 */
openvrml::material_node::~material_node() OPENVRML_NOTHROW
{}

/**
 * @brief Cast to a @c material_node.
 *
 * @return a pointer to this @c material_node.
 */
openvrml::material_node * openvrml::material_node::to_material()
    OPENVRML_NOTHROW
{
    return this;
}

/**
 * @brief Get the ambient intensity.
 *
 * This function delegates to @c #do_ambient_intensity.
 *
 * @return the ambient intensity.
 */
float openvrml::material_node::ambient_intensity() const OPENVRML_NOTHROW
{
    return this->do_ambient_intensity();
}

/**
 * @fn float openvrml::material_node::do_ambient_intensity() const
 *
 * @brief Get the ambient intensity.
 *
 * @return the ambient intensity.
 */

/**
 * @brief Get the diffuse color.
 *
 * This function delegatest to @c #do_diffuse_color.
 *
 * @return the diffuse color.
 */
const openvrml::color & openvrml::material_node::diffuse_color() const
    OPENVRML_NOTHROW
{
    return this->do_diffuse_color();
}

/**
 * @fn const openvrml::color & openvrml::material_node::do_diffuse_color() const
 *
 * @brief Get the diffuse color.
 *
 * @return the diffuse color.
 */

/**
 * @brief Get the emissive color.
 *
 * This function delegates to @c #do_emissive_color.
 *
 * @return the emissive color.
 */
const openvrml::color & openvrml::material_node::emissive_color() const
    OPENVRML_NOTHROW
{
    return this->do_emissive_color();
}

/**
 * @fn const openvrml::color & openvrml::material_node::do_emissive_color() const
 *
 * @brief Get the emissive color.
 *
 * @return the emissive color.
 */

/**
 * @brief Get the shininess.
 *
 * This function delegates to @c #do_shininess.
 *
 * @return the shininess.
 */
float openvrml::material_node::shininess() const OPENVRML_NOTHROW
{
    return this->do_shininess();
}

/**
 * @fn float openvrml::material_node::do_shininess() const
 *
 * @brief Get the shininess.
 *
 * @return the shininess.
 */

/**
 * @brief Get the specular color.
 *
 * This function delegates to @c #do_specular_color.
 *
 * @return the specular color.
 */
const openvrml::color & openvrml::material_node::specular_color() const
    OPENVRML_NOTHROW
{
    return this->do_specular_color();
}

/**
 * @fn const openvrml::color & openvrml::material_node::do_specular_color() const
 *
 * @brief Get the specular color.
 *
 * @return the specular color.
 */

/**
 * @brief Get the transparency.
 *
 * This function delegates to @c #do_transparency.
 *
 * @return the transparency.
 */
float openvrml::material_node::transparency() const OPENVRML_NOTHROW
{
    return this->do_transparency();
}

/**
 * @fn float openvrml::material_node::do_transparency() const
 *
 * @brief Get the transparency.
 *
 * @return the transparency.
 */


/**
 * @class openvrml::navigation_info_node openvrml/node.h
 *
 * @brief Abstract base class for normal nodes.
 */

/**
 * @brief Construct.
 *
 * @param[in] t     the @c node_type associated with the node.
 * @param[in] scope the @c scope the node belongs to.
 */
openvrml::navigation_info_node::
navigation_info_node(const node_type & t,
                     const boost::shared_ptr<openvrml::scope> & scope)
    OPENVRML_NOTHROW:
    node(t, scope)
{}

/**
 * @brief Destroy.
 */
openvrml::navigation_info_node::~navigation_info_node() OPENVRML_NOTHROW
{}

/**
 * @brief Cast to a @c navigation_info_node.
 *
 * @return a pointer to this @c navigation_info_node.
 */
openvrml::navigation_info_node *
openvrml::navigation_info_node::to_navigation_info() OPENVRML_NOTHROW
{
    return this;
}

/**
 * @brief Get the avatar dimensions.
 *
 * This function delegates to @c #do_avatar_size.
 *
 * @return the avatar dimensions.
 */
const std::vector<float> & openvrml::navigation_info_node::avatar_size() const
    OPENVRML_NOTHROW
{
    return this->do_avatar_size();
}

/**
 * @fn const std::vector<float> & openvrml::navigation_info_node::do_avatar_size() const
 *
 * @brief Get the avatar dimensions.
 *
 * @return the avatar dimensions.
 */

/**
 * @brief Get the state of the headlight.
 *
 * This function delegates to @c #do_headlight.
 *
 * @return @c true if the headlight is on; @c false otherwise.
 */
bool openvrml::navigation_info_node::headlight() const OPENVRML_NOTHROW
{
    return this->do_headlight();
}

/**
 * @fn bool openvrml::navigation_info_node::do_headlight() const
 *
 * @brief Get the state of the headlight.
 *
 * @return @c true if the headlight is on; @c false otherwise.
 */

/**
 * @brief Get the current speed of the user view.
 *
 * This function delegates to @c #do_speed.
 *
 * @return the current speed of the user view.
 */
float openvrml::navigation_info_node::speed() const OPENVRML_NOTHROW
{
    return this->do_speed();
}

/**
 * @fn float openvrml::navigation_info_node::do_speed() const
 *
 * @brief Get the current speed of the user view.
 *
 * @return the current speed of the user view.
 */

/**
 * @brief Get the navigation type.
 *
 * This function delegates to @c do_type.
 *
 * @return the navigation type.
 */
const std::vector<std::string> & openvrml::navigation_info_node::type() const
    OPENVRML_NOTHROW
{
    return this->do_type();
}

/**
 * @fn const std::vector<std::string> & openvrml::navigation_info_node::do_type() const
 *
 * @brief Get the navigation type.
 *
 * @return the navigation type.
 */

/**
 * @brief Get the visibility limit.
 *
 * This function delegates to @c #do_visibility_limit.
 *
 * @return the visibility limit.
 */
float openvrml::navigation_info_node::visibility_limit() const OPENVRML_NOTHROW
{
    return this->do_visibility_limit();
}

/**
 * @fn float openvrml::navigation_info_node::do_visibility_limit() const
 *
 * @brief Get the visibility limit.
 *
 * @return the visibility limit.
 */


/**
 * @class openvrml::normal_node openvrml/node.h
 *
 * @brief Abstract base class for normal nodes.
 */

/**
 * @brief Construct.
 *
 * @param[in] type  the @c node_type associated with the node.
 * @param[in] scope the @c scope the node belongs to.
 */
openvrml::normal_node::
normal_node(const node_type & type,
            const boost::shared_ptr<openvrml::scope> & scope)
    OPENVRML_NOTHROW:
    node(type, scope)
{}

/**
 * @brief Destroy.
 */
openvrml::normal_node::~normal_node() OPENVRML_NOTHROW
{}

/**
 * @brief Cast to a @c normal_node.
 *
 * @return a pointer to this @c normal_node.
 */
openvrml::normal_node * openvrml::normal_node::to_normal() OPENVRML_NOTHROW
{
    return this;
}

/**
 * @brief Get the array of normal vectors.
 *
 * This function delegates to @c #do_vector.
 *
 * @return the array of normal vectors.
 */
const std::vector<openvrml::vec3f> & openvrml::normal_node::vector() const
    OPENVRML_NOTHROW
{
    return this->do_vector();
}

/**
 * @fn const std::vector<openvrml::vec3f> & openvrml::normal_node::do_vector() const
 *
 * @brief Get the array of normal vectors.
 *
 * @return the array of normal vectors.
 */


/**
 * @class openvrml::pointing_device_sensor_node openvrml/node.h
 *
 * @brief A node that can be affected by a pointing device.
 */

/**
 * @brief Construct.
 *
 * @param[in] type  the @c node_type.
 * @param[in] scope the @c scope to which the node belongs.
 */
openvrml::pointing_device_sensor_node::
pointing_device_sensor_node(const node_type & type,
                            const boost::shared_ptr<openvrml::scope> & scope):
    node(type, scope),
    bounded_volume_node(type, scope),
    child_node(type, scope)
{}

/**
 * @brief Destroy.
 */
openvrml::pointing_device_sensor_node::~pointing_device_sensor_node()
    OPENVRML_NOTHROW
{}

/**
 * @brief Convey a pointing device state change.
 *
 * This function delegates to @c #do_activate.
 *
 * @param[in] timestamp the current time.
 * @param[in] over      whether the pointing device is over the geometry affected
 *                      by the pointing device sensor.
 * @param[in] active    whether the pointing device is &ldquo;active&rdquo;;
 *                      e.g., whether a mouse button is currently depressed.
 * @param[in] point     the position of the pointer on the affected geometry.
 */
void openvrml::pointing_device_sensor_node::activate(double timestamp,
                                                     bool over,
                                                     bool active,
                                                     const double (&point)[3])
{
    this->do_activate(timestamp, over, active, point);
}

/**
 * @fn void openvrml::pointing_device_sensor_node::do_activate(double timestamp, bool over, bool active, const double (&point)[3])
 *
 * @brief Called to convey a pointing device state change.
 *
 * @param[in] timestamp the current time.
 * @param[in] over      whether the pointing device is over the geometry affected
 *                      by the pointing device sensor.
 * @param[in] active    whether the pointing device is &ldquo;active&rdquo;;
 *                      e.g., whether a mouse button is currently depressed.
 * @param[in] point     the position of the pointer on the affected geometry.
 */

/**
 * @internal
 *
 * @brief Cast to a @c pointing_device_sensor_node.
 *
 * @return a pointer to the object.
 */
openvrml::pointing_device_sensor_node *
openvrml::pointing_device_sensor_node::to_pointing_device_sensor()
    OPENVRML_NOTHROW
{
    return this;
}


/**
 * @class openvrml::scoped_light_node openvrml/node.h
 *
 * @brief A light that falls within a specified area.
 */

/**
 * @brief Construct.
 *
 * @param[in] type  the @c node_type.
 * @param[in] scope the @c scope to which the @c node belongs.
 */
openvrml::scoped_light_node::
scoped_light_node(const node_type & type,
                  const boost::shared_ptr<openvrml::scope> & scope)
    OPENVRML_NOTHROW:
    node(type, scope),
    bounded_volume_node(type, scope),
    child_node(type, scope),
    light_node(type, scope)
{}

/**
 * @brief Destroy.
 */
openvrml::scoped_light_node::~scoped_light_node() OPENVRML_NOTHROW
{}

/**
 * @brief Render the light.
 *
 * Delegates to @c #do_render_scoped_light.
 *
 * @param[in,out] v a viewer.
 */
void openvrml::scoped_light_node::render_scoped_light(viewer & v)
{
    using boost::shared_lock;
    using boost::shared_mutex;
    shared_lock<shared_mutex> lock(this->scene_mutex());
    if (this->scene()) {
        this->do_render_scoped_light(v);
    }
}

/**
 * @brief Convert to a @c scoped_light_node.
 *
 * @return a pointer to the instance.
 */
openvrml::scoped_light_node * openvrml::scoped_light_node::to_scoped_light()
    OPENVRML_NOTHROW
{
    return this;
}

/**
 * @fn void openvrml::scoped_light_node::do_render_scoped_light(viewer & v)
 *
 * @brief Render the light.
 *
 * @param[in,out] v a @c viewer.
 */


/**
 * @class openvrml::sound_source_node openvrml/node.h
 *
 * @brief Abstract base class for sound source nodes.
 */

/**
 * @brief Constructor.
 *
 * @param[in] type  the @c node_type associated with the @c node.
 * @param[in] scope the @c scope the @c node belongs to.
 */
openvrml::sound_source_node::
sound_source_node(const node_type & type,
                  const boost::shared_ptr<openvrml::scope> & scope)
    OPENVRML_NOTHROW:
    node(type, scope)
{}

/**
 * @brief Destructor.
 */
openvrml::sound_source_node::~sound_source_node() OPENVRML_NOTHROW
{}

/**
 * @brief Cast to a @c sound_source_node.
 *
 * @return a pointer to this @c sound_source_node.
 */
openvrml::sound_source_node * openvrml::sound_source_node::to_sound_source()
    OPENVRML_NOTHROW
{
    return this;
}


/**
 * @class openvrml::texture_node openvrml/node.h
 *
 * @brief Abstract base class for texture nodes.
 */

/**
 * @brief Construct.
 *
 * @param[in] type  the @c node_type associated with the @c node.
 * @param[in] scope the @c scope the @c node belongs to.
 */
openvrml::texture_node::
texture_node(const node_type & type,
             const boost::shared_ptr<openvrml::scope> & scope)
    OPENVRML_NOTHROW:
    node(type, scope)
{}

/**
 * @brief Destroy.
 */
openvrml::texture_node::~texture_node() OPENVRML_NOTHROW
{}

/**
 * @brief Insert a texture into a viewer.
 *
 * @param[in,out] v viewer.
 */
void openvrml::texture_node::render_texture(viewer & v)
{
    using boost::shared_lock;
    using boost::shared_mutex;
    shared_lock<shared_mutex> lock(this->scene_mutex());

    if (!this->scene()) { return; }

    if (this->modified()) { v.remove_texture_object(*this); }

    this->do_render_texture(v);
    this->modified(false);
}

/**
 * @brief @c #render_texture implementation.
 *
 * @param[in,out] v viewer.
 */
void openvrml::texture_node::do_render_texture(viewer &)
{}

/**
 * @brief Cast to a @c texture_node.
 *
 * @return a pointer to this @c texture_node.
 */
openvrml::texture_node * openvrml::texture_node::to_texture() OPENVRML_NOTHROW
{
    return this;
}


/**
 * @brief The image.
 *
 * This function delegates to @c #do_image.
 *
 * @return the image.
 */
const openvrml::image & openvrml::texture_node::image() const
    OPENVRML_NOTHROW
{
    return this->do_image();
}

/**
 * @fn const openvrml::image & openvrml::texture_node::do_image() const
 *
 * @brief The image.
 *
 * @return the image.
 */

/**
 * @brief Get the flag indicating whether the texture should repeat in the
 *      <var>S</var> direction.
 *
 * This function delegates to @c #do_repeat_s.
 *
 * @return @c true if the image should repeat in the <var>S</var> direction,
 *      @c false otherwise.
 */
bool openvrml::texture_node::repeat_s() const OPENVRML_NOTHROW
{
    return this->do_repeat_s();
}

/**
 * @fn bool openvrml::texture_node::do_repeat_s() const
 *
 * @brief Get the flag indicating whether the texture should repeat in the
 *      <var>S</var> direction.
 *
 * @return @c true if the image should repeat in the <var>S</var> direction,
 *      @c false otherwise.
 */

/**
 * @brief Get the flag indicating whether the texture should repeat in the
 *      <var>T</var> direction.
 *
 * This function delegates to @c #do_repeat_t.
 *
 * @return @c true if the image should repeat in the <var>T</var> direction,
 *      @c false otherwise.
 */
bool openvrml::texture_node::repeat_t() const OPENVRML_NOTHROW
{
    return this->do_repeat_t();
}

/**
 * @fn bool openvrml::texture_node::do_repeat_t() const
 *
 * @brief Get the flag indicating whether the texture should repeat in the
 *      <var>T</var> direction.
 *
 * @return @c true if the image should repeat in the <var>T</var> direction,
 *      @c false otherwise.
 */


/**
 * @class openvrml::texture_coordinate_node openvrml/node.h
 *
 * @brief Abstract base class for texture coordinate nodes.
 */

/**
 * @brief Construct.
 *
 * @param[in] type  the @c node_type associated with the @c node.
 * @param[in] scope the @c scope the @c node belongs to.
 */
openvrml::texture_coordinate_node::
texture_coordinate_node(const node_type & type,
                        const boost::shared_ptr<openvrml::scope> & scope)
    OPENVRML_NOTHROW:
    node(type, scope)
{}

/**
 * @brief Destroy.
 */
openvrml::texture_coordinate_node::~texture_coordinate_node() OPENVRML_NOTHROW
{}

/**
 * @brief Cast to a @c texture_coordinate_node.
 *
 * @return a pointer to this @c texture_coordinate_node.
 */
openvrml::texture_coordinate_node *
openvrml::texture_coordinate_node::to_texture_coordinate()
    OPENVRML_NOTHROW
{
    return this;
}

/**
 * @brief The texture coordinates.
 *
 * This function delegates to @c #do_point.
 *
 * @return the texture coordinates.
 */
const std::vector<openvrml::vec2f> &
openvrml::texture_coordinate_node::point() const OPENVRML_NOTHROW
{
    return this->do_point();
}

/**
 * @fn const std::vector<openvrml::vec2f> & openvrml::texture_coordinate_node::do_point() const
 *
 * @brief The texture coordinates.
 *
 * @return the texture coordinates.
 */


/**
 * @class openvrml::texture_transform_node openvrml/node.h
 *
 * @brief Abstract base class for texture transform nodes.
 */

/**
 * @brief Construct.
 *
 * @param[in] type  the @c node_type associated with the @c node.
 * @param[in] scope the @c scope the @c node belongs to.
 */
openvrml::texture_transform_node::
texture_transform_node(const node_type & type,
                       const boost::shared_ptr<openvrml::scope> & scope)
    OPENVRML_NOTHROW:
    node(type, scope)
{}

/**
 * @brief Destructor.
 */
openvrml::texture_transform_node::~texture_transform_node() OPENVRML_NOTHROW
{}

/**
 * @brief Render the texture transform.
 *
 * @param[in,out] v viewer.
 */
void openvrml::texture_transform_node::render_texture_transform(viewer & v)
{
    using boost::shared_lock;
    using boost::shared_mutex;
    shared_lock<shared_mutex> lock(this->scene_mutex());
    if (this->scene()) {
        this->do_render_texture_transform(v);
        this->modified(false);
    }
}

/**
 * @brief Render the texture transform.
 *
 * @param[in,out] v viewer.
 */
void openvrml::texture_transform_node::do_render_texture_transform(viewer &)
{}

/**
 * @brief Cast to a @c texture_transform_node.
 *
 * @return a pointer to this @c texture_transform_node.
 */
openvrml::texture_transform_node *
openvrml::texture_transform_node::to_texture_transform()
    OPENVRML_NOTHROW
{
    return this;
}

/**
 * @class openvrml::time_dependent_node openvrml/node.h
 *
 * @brief Abstract base class for time-dependent nodes.
 */

/**
 * @brief Construct.
 *
 * @param[in] type  the @c node_type associated with the @c node.
 * @param[in] scope the @c scope the @c node belongs to.
 */
openvrml::time_dependent_node::
time_dependent_node(const node_type & type,
                    const boost::shared_ptr<openvrml::scope> & scope)
    OPENVRML_NOTHROW:
    node(type, scope)
{}

/**
 * @brief Destroy.
 */
openvrml::time_dependent_node::~time_dependent_node() OPENVRML_NOTHROW
{}

/**
 * @brief Update with the current time.
 *
 * This function delegates to @c #do_update.
 *
 * @param[in] time  the current time.
 */
void openvrml::time_dependent_node::update(double time)
{
    this->do_update(time);
}

/**
 * @fn void openvrml::time_dependent_node::do_update(double time)
 *
 * @brief Update with the current time.
 *
 * @param[in] time  the current time.
 */

/**
 * @brief Cast to a @c time_dependent_node.
 *
 * @return a pointer to the object.
 */
openvrml::time_dependent_node *
openvrml::time_dependent_node::to_time_dependent() OPENVRML_NOTHROW
{
    return this;
}


/**
 * @class openvrml::transform_node openvrml/node.h
 *
 * @brief Abstract base class for transform nodes.
 */

/**
 * @brief Construct.
 *
 * @param[in] type  the @c node_type associated with the @c node.
 * @param[in] scope the @c scope the @c node belongs to.
 */
openvrml::transform_node::
transform_node(const node_type & type,
               const boost::shared_ptr<openvrml::scope> & scope)
    OPENVRML_NOTHROW:
    node(type, scope),
    bounded_volume_node(type, scope),
    child_node(type, scope),
    grouping_node(type, scope)
{}

/**
 * @brief Destroy.
 */
openvrml::transform_node::~transform_node() OPENVRML_NOTHROW
{}

/**
 * @brief Cast to a @c transform_node.
 *
 * @return a pointer to this @c transform_node.
 */
openvrml::transform_node * openvrml::transform_node::to_transform()
    OPENVRML_NOTHROW
{
    return this;
}

/**
 * @brief Get the transformation associated with the @c node as a matrix.
 *
 * This function delegates to @c #do_transform.
 *
 * @return the transformation associated with the @c node.
 */
const openvrml::mat4f & openvrml::transform_node::transform() const
    OPENVRML_NOTHROW
{
    return this->do_transform();
}

/**
 * @fn const openvrml::mat4f & openvrml::transform_node::do_transform() const
 *
 * @brief Get the transformation associated with the @c node as a matrix.
 *
 * @return the transformation associated with the @c node.
 */


/**
 * @class openvrml::viewpoint_node openvrml/node.h
 *
 * @brief Abstract base class for viewpoint nodes.
 */

/**
 * @brief Constructor.
 *
 * @param[in] type  the @c node_type associated with the @c node.
 * @param[in] scope the @c scope the @c node belongs to.
 */
openvrml::viewpoint_node::
viewpoint_node(const node_type & type,
               const boost::shared_ptr<openvrml::scope> & scope)
    OPENVRML_NOTHROW:
    node(type, scope)
{}

/**
 * @brief Destructor.
 */
openvrml::viewpoint_node::~viewpoint_node() OPENVRML_NOTHROW
{}

/**
 * @brief Cast to a @c viewpoint_node.
 *
 * @return a pointer to this @c viewpoint_node.
 */
openvrml::viewpoint_node * openvrml::viewpoint_node::to_viewpoint()
    OPENVRML_NOTHROW
{
    return this;
}

/**
 * @brief Get the transformation of the @c viewpoint_node in the global
 *        coordinate system.
 *
 * This function delegates to @c #do_transformation.
 *
 * @return the transformation of the @c viewpoint_node in the global coordinate
 *         system.
 */
const openvrml::mat4f & openvrml::viewpoint_node::transformation() const
    OPENVRML_NOTHROW
{
    return this->do_transformation();
}

/**
 * @fn const openvrml::mat4f & openvrml::viewpoint_node::do_transformation() const
 *
 * @brief Get the transformation of the @c viewpoint_node in the global
 *        coordinate system.
 *
 * @return the transformation of the @c viewpoint_node in the global coordinate
 *         system.
 */

/**
 * @brief Get the transformation of the user view relative to the
 *      @c viewpoint_node.
 *
 * This function delegates to @c #do_user_view_transform().
 *
 * @return the transformation of the user view relative to the
 *         @c viewpoint_node.
 */
const openvrml::mat4f & openvrml::viewpoint_node::user_view_transform() const
    OPENVRML_NOTHROW
{
    return this->do_user_view_transform();
}

/**
 * @fn const openvrml::mat4f & openvrml::viewpoint_node::do_user_view_transform() const
 *
 * @brief Get the transformation of the user view relative to the
 *      @c viewpoint_node.
 *
 * @return the transformation of the user view relative to the
 *         @c viewpoint_node.
 */

/**
 * @brief Set the transformation of the user view relative to the
 *        @c viewpoint_node.
 *
 * This function delegates to @c #do_user_view_transform(const mat4f &).
 *
 * @param[in] transform the new transformation.
 */
void openvrml::viewpoint_node::user_view_transform(const mat4f & transform)
    OPENVRML_NOTHROW
{
    this->do_user_view_transform(transform);
}

/**
 * @fn void openvrml::viewpoint_node::do_user_view_transform(const mat4f & transform)
 *
 * @brief Set the transformation of the user view relative to the
 *        @c viewpoint_node.
 *
 * @param[in] transform the new transformation.
 */

/**
 * @brief Get the description.
 *
 * This function delegates to @c #do_description.
 *
 * @return the description.
 */
const std::string & openvrml::viewpoint_node::description() const
    OPENVRML_NOTHROW
{
    return this->do_description();
}

/**
 * @fn const std::string & openvrml::viewpoint_node::do_description() const
 *
 * @brief Get the description.
 *
 * @return the description.
 */

/**
 * @brief Get the field of view.
 *
 * This function delegates to @c #do_field_of_view.
 *
 * @return the field of view in radians.
 */
float openvrml::viewpoint_node::field_of_view() const OPENVRML_NOTHROW
{
    return this->do_field_of_view();
}

/**
 * @fn float openvrml::viewpoint_node::do_field_of_view() const
 *
 * @brief Get the field of view.
 *
 * @return the field of view in radians.
 */


/**
 * @class openvrml::node_traverser openvrml/node.h
 *
 * @brief Traverse the children of each @c node in a @c node hierarchy only
 *        once.
 *
 * The @c node_traverser provides a generalized traversal mechanism that
 * avoids redundantly traversing branches of the @c node hierarchy.  If a
 * @c node occurs multiple places in a branch, <strong>the children of that
 * @c node will be visited in the traversal only once</strong>.
 *
 * For each @c node encountered in the traversal, @c node_traverser does the
 * following:
 *
 * -# Call @c #on_entering.
 * -# Traverse descendants, if any.
 * -# Call @c #on_leaving.
 *
 * Concrete subclasses of @c node_traverser implement the @c #on_entering
 * and/or @c #on_leaving member functions in order to perform some operation(s)
 * on each node.  The traversal can be ended prematurely by calling
 * @c #halt_traversal.
 */

/**
 * @internal
 *
 * @var std::set<openvrml::node *> openvrml::node_traverser::traversed_nodes
 *
 * @brief The set of @c node%s that have already been traversed.
 */

/**
 * @internal
 *
 * @var bool openvrml::node_traverser::halt
 *
 * @brief Flag to indicate if the traversal should be halted.
 */

/**
 * @brief Construct.
 *
 * @exception std::bad_alloc    if memory allocation fails.
 */
openvrml::node_traverser::node_traverser() OPENVRML_THROW1(std::bad_alloc):
    halt(false)
{}

/**
 * @brief Destroy.
 */
openvrml::node_traverser::~node_traverser() OPENVRML_NOTHROW
{}

/**
 * @brief Traverse a @c node.
 *
 * No guarantee is made about the state of the @c node_traverser instance in
 * the event that this method throws.
 *
 * In addition to @c std::bad_alloc, this function throws any exception thrown
 * from @c #on_entering or @c #on_leaving.
 *
 * @param[in,out] n  the root @c node of the branch to traverse.
 *
 * @exception std::bad_alloc    if memory allocation fails.
 */
void openvrml::node_traverser::traverse(node & n)
{
    assert(this->traversed_nodes.empty());
    try {
        this->do_traversal(n);
    } catch (...) {
        this->halt = false;
        this->traversed_nodes.clear();
        throw;
    }
    this->halt = false;
    this->traversed_nodes.clear();
}

/**
 * @overload
 *
 * @brief Traverse a @c node.
 *
 * @param[in,out] node  the root node of the branch to traverse.
 *
 * @exception std::bad_alloc    if memory allocation fails.
 */
void
openvrml::node_traverser::traverse(const boost::intrusive_ptr<node> & node)
{
    assert(this->traversed_nodes.empty());
    try {
        if (node) {
            if (this->traversed_nodes.find(node.get())
                    == this->traversed_nodes.end()) {
                this->do_traversal(*node);
            }
        }
    } catch (...) {
        this->halt = false;
        this->traversed_nodes.clear();
        throw;
    }
    this->halt = false;
    this->traversed_nodes.clear();
}

/**
 * @brief Traverse a @c std::vector of @c node%s.
 *
 * @overload
 *
 * @param[in,out] nodes the root @link openvrml::node nodes@endlink of the
 *                      branch to traverse.
 */
void
openvrml::node_traverser::
traverse(const std::vector<boost::intrusive_ptr<node> > & nodes)
{
    assert(this->traversed_nodes.empty());
    try {
        typedef std::vector<boost::intrusive_ptr<node> > nodes_t;
        for (nodes_t::const_iterator node(nodes.begin());
             node != nodes.end() && !this->halt;
             ++node) {
            if (*node) {
                if (this->traversed_nodes.find(node->get())
                        == this->traversed_nodes.end()) {
                    this->do_traversal(**node);
                }
            }
        }
    } catch (...) {
        this->halt = false;
        this->traversed_nodes.clear();
        throw;
    }
    this->halt = false;
    this->traversed_nodes.clear();
}

/**
 * @brief Halt the traversal.
 *
 * If this method is called during a traversal, no more descendant @c node%s
 * will be traversed.  Note that if @c #halt_traversal is called in the
 * implementation of @c #on_entering, @c #on_leaving will still be called for
 * the current node and any parent nodes (that is, any node for which
 * @c #on_entering has been called).  Implementations of @c #on_leaving can
 * call @c #halted to check whether the traversal has been halted.
 */
void openvrml::node_traverser::halt_traversal() OPENVRML_NOTHROW
{
    this->halt = true;
}

/**
 * @brief Indicate whether the traversal has been halted.
 *
 * This function is useful in implementations of @c #on_leaving that need to
 * check whether the traversal has been halted.
 *
 * @return @c true if the traversal has been halted; @c false otherwise.
 */
bool openvrml::node_traverser::halted() const OPENVRML_NOTHROW
{
    return this->halt;
}

/**
 * @brief Check whether a @c node has been traversed.
 *
 * @param[in] n the @c node to check.
 *
 * @return @c true if @p n has been traversed; @c false otherwise.
 */
bool openvrml::node_traverser::traversed(node & n) const OPENVRML_NOTHROW
{
    return this->traversed_nodes.find(&n) != this->traversed_nodes.end();
}

/**
 * @internal
 *
 * @brief Traverse a @c node.
 *
 * @param[in,out] n  the @c node to traverse.
 *
 * @exception std::bad_alloc    if memory allocation fails.
 */
void openvrml::node_traverser::do_traversal(node & n)
{
    std::set<node *>::iterator pos = this->traversed_nodes.find(&n);
    const bool alreadyTraversed = (pos != this->traversed_nodes.end());

    if (!alreadyTraversed) {
        this->on_entering(n);

        this->traversed_nodes.insert(&n);

        const node_interface_set & interfaces = n.type().interfaces();
        for (node_interface_set::const_iterator interface_(interfaces.begin());
                interface_ != interfaces.end() && !this->halt; ++interface_) {
            if (interface_->type == node_interface::field_id
                    || interface_->type == node_interface::exposedfield_id) {
                if (interface_->field_type == field_value::sfnode_id) {
                    const sfnode value = n.field<sfnode>(interface_->id);
                    if (value.value()) {
                        this->do_traversal(*value.value());
                    }
                } else if (interface_->field_type == field_value::mfnode_id) {
                    const mfnode children = n.field<mfnode>(interface_->id);
                    for (size_t i = 0;
                         i < children.value().size() && !this->halt;
                         ++i) {
                        if (children.value()[i]) {
                            this->do_traversal(*children.value()[i]);
                        }
                    }
                }
            }
        }
        this->on_leaving(n);
    }
}

/**
 * @brief Called for each @c node in the traversal @e before
 *        traversing the its descendants.
 *
 * @param[in,out] n  the @c node currently being traversed.
 */
void openvrml::node_traverser::on_entering(node &)
{}

/**
 * @brief Called for each @c node in the traversal @e after
 *        traversing the its descendants.
 *
 * @param[in,out] n  the @c node currently being traversed.
 */
void openvrml::node_traverser::on_leaving(node &)
{}
