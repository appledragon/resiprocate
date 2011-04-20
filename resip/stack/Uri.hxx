#if !defined(RESIP_URI_HXX)
#define RESIP_URI_HXX 

#include <bitset>
#include <cassert>

#include "resip/stack/ParserCategory.hxx"
#include "resip/stack/Token.hxx"
#include "rutil/TransportType.hxx"
#include "rutil/HeapInstanceCounter.hxx"

#define URI_ENCODING_TABLE_SIZE 256

namespace resip
{
class SipMessage;

class Uri : public ParserCategory
{
   public:
      RESIP_HeapCount(Uri);
      
      Uri();
      Uri(const Uri&);
      explicit Uri(const Data& data);

      ~Uri();
      
      // convert from a tel scheme to sip scheme, adds user=phone param
      //static Uri fromTel(const Uri&, const Data& host);  // deprecate...
      static Uri fromTel(const Uri&, const Uri& hostUri);

      Data& host() {checkParsed(); return mHost;}
      const Data& host() const {checkParsed(); return mHost;}
      Data& user() {checkParsed(); return mUser;}
      const Data& user() const {checkParsed(); return mUser;}
      Data& userParameters() {checkParsed(); return mUserParameters;}
      const Data& userParameters() const {checkParsed(); return mUserParameters;}
      Data& opaque() {checkParsed(); return mHost;}
      const Data& opaque() const {checkParsed(); return mHost;}

      // Returns user@host[:port] (no scheme)
      const Data& getAor() const;
      // Returns user@host (no scheme or port)
      const Data getAorNoPort() const;

      // Actually returns the AOR; <scheme>:<user>@<host>[:<port>]
      Data getAorNoReally() const;
      //strips all paramters - if transport type is specified (ie. not UNKNOWN_TRANSPORT),
      //and the default port for the transport is on the Aor, then it is removed
      Uri getAorAsUri(TransportType transportTypeToRemoveDefaultPort = UNKNOWN_TRANSPORT) const;
      

      /**
         Returns true if the user appears to fit the BNF for the 
         'telephone-subscriber' element in the RFC 3261 (and by extension, RFC 
         3966) grammar. This is important because 'telephone-subscriber' can 
         have parameters, which you could then access easily through the
         getUserAsTelephoneSubscriber() and setUserAsTelephoneSubscriber() 
         calls.
      */
      bool userIsTelephoneSubscriber() const;

      /**
         Returns the user-part as a 'telephone-subscriber' grammar element (in 
         other words, this parses the user-part into a dial string and 
         parameters, with the dial-string accessible with Token::value(), and 
         the parameters accessible with the various Token::param() and 
         Token::exists() interfaces). 
         
         For example, suppose the following is in the Request-URI:
         
         sip:5555551234;phone-context=+86\@example.com;user=dialstring
         
         The user-part of this SIP URI is "5555551234;phone-context=+86", and it
         fits the BNF for the 'telephone-subscriber' grammar element. To access 
         the 'phone-context' parameter, do something like the following:

         @code
            Uri& reqUri(sip.header(h_RequestLine).uri());

            // !bwc! May add native support for this param later
            static ExtensionParameter p_phoneContext("phone-context");
            Data phoneContextValue;

            if(reqUri.isWellFormed())
            {
               if(reqUri.exists(p_phoneContext))
               {
                  // Phone context as URI param
                  phoneContextValue=reqUri.param(p_phoneContext);
               }
               else if(reqUri.scheme()=="sip" || reqUri.scheme()=="sips")
               {
                  // Might have phone-context as a user param (only happens 
                  // in a sip or sips URI)
                  // Technically, this userIsTelephoneSubscriber() check is 
                  // required: 
                  // sip:bob;phone-context=+86@example.com doesn't have a 
                  // phone-context param according to the BNF in 3261. But, 
                  // interop may require you to parse this as if it did have 
                  // such a param.
                  if(reqUri.userIsTelephoneSubscriber())
                  {
                     Token telSub(reqUri.getUserAsTelephoneSubscriber());
                     if(telSub.isWellFormed() && telSub.exists(p_phoneContext))
                     {
                        // Phone context as user param
                        phoneContextValue=telSub.param(p_phoneContext);
                     }
                  }
               }
            }
         @endcode
      */
      Token getUserAsTelephoneSubscriber() const;

      /**
         Sets the user-part of this URI using the dial-string and parameters 
         stored in telephoneSubscriber.
         @param telephoneSubscriber The user-part, as a 'telephone-subscriber'
            grammar element.
      */
      void setUserAsTelephoneSubscriber(const Token& telephoneSubscriber);


      Data& scheme() {checkParsed(); return mScheme;}
      const Data& scheme() const {checkParsed(); return mScheme;}
      int& port() {checkParsed(); return mPort;}
      int port() const {checkParsed(); return mPort;}
      Data& password() {checkParsed(); return mPassword;}
      const Data& password() const {checkParsed(); return mPassword;}

      Data toString() const;

      /** Returns true if the uri can be converted into a string that can be
          used as an enum lookup */
      bool isEnumSearchable() const;

      /** Return a vector of domains to do a NAPTR lookup for enum */
      std::vector<Data> getEnumLookups(const std::vector<Data>& suffixes) const;

      /** Modifies the default URI encoding character sets */
      static void setUriUserEncoding(char c, bool encode);
      static void setUriPasswordEncoding(char c, bool encode);
      
      bool hasEmbedded() const;
      SipMessage& embedded();
      const SipMessage& embedded() const;

      void removeEmbedded();

      virtual void parse(ParseBuffer& pb);
      virtual ParserCategory* clone() const;
      virtual EncodeStream& encodeParsed(EncodeStream& str) const;
      
      // parse the headers into this as SipMessage
      void parseEmbeddedHeaders(ParseBuffer& pb);
      EncodeStream& encodeEmbeddedHeaders(EncodeStream& str) const;

      Uri& operator=(const Uri& rhs);
      bool operator==(const Uri& other) const;
      bool operator!=(const Uri& other) const;
      bool operator<(const Uri& other) const;
      
   protected:
      Data mScheme;
      Data mHost;
      Data mUser;
      Data mUserParameters;
      int mPort;
      mutable Data mAor;
      Data mPassword;

      // cache for aor
      mutable Data mOldScheme;
      mutable Data mOldHost;
      mutable Data mOldUser;
      mutable int mOldPort;

      // cache for IPV6 host comparison
      mutable Data mCanonicalHost;

      static bool mEncodingReady;
      // characters listed in these strings should not be URI encoded
      static Data mUriNonEncodingUserChars;
      static Data mUriNonEncodingPasswordChars;
      static const Data mLocalNumberChars;
      static const Data mGlobalNumberChars;
      typedef std::bitset<URI_ENCODING_TABLE_SIZE> EncodingTable;
      // if a bit is set/true, the corresponding character should be encoded
      static EncodingTable mUriEncodingUserTable;
      static EncodingTable mUriEncodingPasswordTable;
      static EncodingTable mLocalNumberTable;
      static EncodingTable mGlobalNumberTable;

      static void initialiseEncodingTables();
      static inline bool shouldEscapeUserChar(char c);
      static inline bool shouldEscapePasswordChar(char c);

   private:
      Data mEmbeddedHeadersText;
      SipMessage* mEmbeddedHeaders;
};

}

#include "rutil/HashMap.hxx"

HashValue(resip::Uri);

#endif

/* ====================================================================
 * The Vovida Software License, Version 1.0 
 * 
 * Copyright (c) 2000 Vovida Networks, Inc.  All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 
 * 3. The names "VOCAL", "Vovida Open Communication Application Library",
 *    and "Vovida Open Communication Application Library (VOCAL)" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact vocal@vovida.org.
 *
 * 4. Products derived from this software may not be called "VOCAL", nor
 *    may "VOCAL" appear in their name, without prior written
 *    permission of Vovida Networks, Inc.
 * 
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND
 * NON-INFRINGEMENT ARE DISCLAIMED.  IN NO EVENT SHALL VOVIDA
 * NETWORKS, INC. OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT DAMAGES
 * IN EXCESS OF $1,000, NOR FOR ANY INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 * 
 * ====================================================================
 * 
 * This software consists of voluntary contributions made by Vovida
 * Networks, Inc. and many individuals on behalf of Vovida Networks,
 * Inc.  For more information on Vovida Networks, Inc., please see
 * <http://www.vovida.org/>.
 *
 */
