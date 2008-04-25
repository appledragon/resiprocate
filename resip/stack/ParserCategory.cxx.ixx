// !bwc! I apologize that this is so ugly. If you know of a standard GNU utility that will re-indent uglified c++ code (like this), let me know...
// Generated by updateParameters.sh 
#define defineParam(_enum, _name, _type, _RFC_ref_ignored)                                                \
_enum##_Param::DType&                                                                                           \
ParserCategory::param(const _enum##_Param& paramType)                                                           \
{                                                                                                               \
   checkParsed();                                                                                               \
   _enum##_Param::Type* p =                                                                                     \
      static_cast<_enum##_Param::Type*>(getParameterByEnum(ParameterTypes::_enum));                             \
   if (!p)                                                                                                      \
   {                                                                                                            \
      p = new _enum##_Param::Type(ParameterTypes::_enum);                                                       \
      mParameters.push_back(p);                                                                                 \
   }                                                                                                            \
   return p->value();                                                                                           \
}                                                                                                               \
                                                                                                                \
const _enum##_Param::DType&                                                                                     \
ParserCategory::param(const _enum##_Param& paramType) const                                                     \
{                                                                                                               \
   checkParsed();                                                                                               \
   _enum##_Param::Type* p =                                                                                     \
      static_cast<_enum##_Param::Type*>(getParameterByEnum(ParameterTypes::_enum));                             \
   if (!p)                                                                                                      \
   {                                                                                                            \
      InfoLog(<< "Missing parameter " _name ); \
      DebugLog(<< *this);                                                                                       \
      throw Exception("Missing parameter " _name, __FILE__, __LINE__);                                        \
   }                                                                                                            \
   return p->value();                                                                                           \
};
// .bwc. This is the file you edit when you want to add native support for a
// parameter to the stack. A few basic facts about how this file is used:
// * Only lines beginning with "defineParam" are processed in any way.
// * The syntax expected is defineParam(<1>, "<2>", <3>, "<4>")
//    1: The postfix for the accessor token; ie dAlg -> p_dAlg
//    2: The name of the parameter, in lower-case, as it will appear on the wire
//    3: The class that will be used to represent the parameter's value
//    4: A reference to where the param was defined
// If you have edited this file, you then need to run updateParameters.sh.

defineParam(audio, "audio", BooleanFeatureParameter , "RFC 3840")
defineParam(automata, "automata", BooleanFeatureParameter , "RFC 3840")
defineParam(Class, "class", QuotedListParameter , "RFC 3840")
defineParam(duplex, "duplex", QuotedDataParameter , "RFC 3840")
defineParam(data, "data", BooleanFeatureParameter , "RFC 3840")
defineParam(control, "control", BooleanFeatureParameter , "RFC 3840")
defineParam(mobility, "mobility", QuotedDataParameter , "RFC 3840")
defineParam(description, "description", QuotedDataParameter , "RFC 3840") // <> quoted
defineParam(events, "events", QuotedListParameter , "RFC 3840")
defineParam(priority, "priority", NumericFeatureParameter , "RFC 3840")
defineParam(methods, "methods", QuotedListParameter , "RFC 3840")
defineParam(extensions, "extensions", QuotedListParameter , "RFC 3840")
defineParam(schemes, "schemes", QuotedListParameter , "RFC 3840")
defineParam(application, "application", BooleanFeatureParameter , "RFC 3840")
defineParam(video, "video", BooleanFeatureParameter , "RFC 3840")
defineParam(language, "language", QuotedListParameter , "RFC 3840")
defineParam(isFocus, "isfocus", BooleanFeatureParameter , "RFC 3840")
defineParam(actor, "actor", QuotedListParameter, "RFC 3840") // principal|msg-defineParam(text, "text", BooleanFeatureParameter , "RFC 3840")
defineParam(Instance, "+sip.instance", QuotedDataParameter, "gruu")  // <> quoted
defineParam(regid, "reg-id", UInt32Parameter, "outbound")  
defineParam(ob,"ob",ExistsParameter,"outbound-05")
defineParam(pubGruu, "pub-gruu", QuotedDataParameter, "gruu")
defineParam(tempGruu, "temp-gruu", QuotedDataParameter, "gruu")
defineParam(gruu, "gruu", QuotedDataParameter, "gruu")
defineParam(accessType, "access-type", DataParameter, "RFC 4483")
defineParam(algorithm, "algorithm", DataParameter, "RFC ????")
defineParam(boundary, "boundary", DataParameter, "RFC 2046")
defineParam(branch, "branch", BranchParameter, "RFC ????")
defineParam(charset, "charset", DataParameter, "RFC 2045")
defineParam(cnonce, "cnonce", QuotedDataParameter, "RFC ????")
defineParam(comp, "comp", DataParameter, "RFC ????")
defineParam(dAlg, "d-alg", DataParameter, "RFC 3329")
defineParam(dQop, "d-qop", DataParameter, "RFC ????")
defineParam(dVer, "d-ver", QuotedDataParameter, "RFC ????")
defineParam(directory, "directory", DataParameter, "RFC 2046")
defineParam(domain, "domain", QuotedDataParameter, "RFC ????")
defineParam(duration, "duration", UInt32Parameter, "RFC ????")
defineParam(expiration, "expiration", QuotedDataParameter, "RFC 2046")
defineParam(expires, "expires", UInt32Parameter, "RFC ????")
defineParam(filename, "filename", DataParameter, "RFC ????")
defineParam(fromTag, "from-tag", DataParameter, "RFC ????")
defineParam(handling, "handling", DataParameter, "RFC ????")
defineParam(id, "id", DataParameter, "RFC ????")
defineParam(lr, "lr", ExistsParameter, "RFC ????")
defineParam(maddr, "maddr", DataParameter, "RFC ????")
defineParam(method, "method", DataParameter, "RFC ????")
defineParam(micalg, "micalg", DataParameter, "RFC 1847")
defineParam(mode, "mode", DataParameter, "RFC 2046")
defineParam(name, "name", DataParameter, "RFC 2046")
defineParam(nc, "nc", DataParameter, "RFC ????")
defineParam(nonce, "nonce", QuotedDataParameter, "RFC ????")
defineParam(opaque, "opaque", QuotedDataParameter, "RFC ????")
defineParam(permission, "permission", DataParameter, "RFC 2046")
defineParam(protocol, "protocol", QuotedDataParameter, "RFC 1847")
defineParam(purpose, "purpose", DataParameter, "RFC ????")
defineParam(q, "q", QValueParameter, "RFC 3261")
defineParam(realm, "realm", QuotedDataParameter, "RFC ????")
defineParam(reason, "reason", DataParameter, "RFC ????")
defineParam(received, "received", DataParameter, "RFC ????")
defineParam(response, "response", QuotedDataParameter, "RFC ????")
defineParam(retryAfter, "retry-after", UInt32Parameter, "RFC ????")
defineParam(rinstance, "rinstance", DataParameter, "")
defineParam(rport, "rport", RportParameter, "RFC ????")
defineParam(server, "server", DataParameter, "RFC 2046")
defineParam(site, "site", DataParameter, "RFC 2046")
defineParam(size, "size", DataParameter, "RFC 2046")
defineParam(smimeType, "smime-type", DataParameter, "RFC 2633")
defineParam(stale, "stale", DataParameter, "RFC ????")
defineParam(tag, "tag", DataParameter, "RFC ????")
defineParam(toTag, "to-tag", DataParameter, "RFC ????")
defineParam(transport, "transport", DataParameter, "RFC ????")
defineParam(ttl, "ttl", UInt32Parameter, "RFC ????")
defineParam(uri, "uri", QuotedDataParameter, "RFC ????")
defineParam(user, "user", DataParameter, "RFC ????")
defineParam(extension, "ext", DataParameter, "RFC ????")
defineParam(username, "username", DataParameter, "RFC ????")
defineParam(earlyOnly, "early-only", ExistsParameter, "RFC 3891")
defineParam(refresher, "refresher", DataParameter, "RFC 4028")
defineParam(profileType, "profile-type", DataParameter, "draft-ietf-sipping-config-framework")
defineParam(vendor, "vendor", DataParameter, "draft-ietf-sipping-config-framework")
defineParam(model, "model", DataParameter, "draft-ietf-sipping-config-framework")
defineParam(version, "version", DataParameter, "draft-ietf-sipping-config-framework")
defineParam(effectiveBy, "effective-by", UInt32Parameter, "draft-ietf-sipping-config-framework")
defineParam(document, "document", DataParameter, "draft-ietf-sipping-config-framework")
defineParam(appId, "app-id", DataParameter, "draft-ietf-sipping-config-framework")
defineParam(networkUser, "network-user", DataParameter, "draft-ietf-sipping-config-framework")
defineParam(url, "url", QuotedDataParameter, "draft-ietf-sip-content-indirect-mech-05")
defineParam(qop, "qop", DataParameter, "RFC 3261")
defineParam(sigcompId, "sigcomp-id", QuotedDataParameter, "draft-ietf-rohc-sigcomp-sip")
// ?bwc? Do we use this any more?
defineParam(addTransport, "addtransport", ExistsParameter, "")
#undef defineParam
