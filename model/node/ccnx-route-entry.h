/*
 * Copyright (c) 2016, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL XEROX OR PARC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/* ################################################################################
 * #
 * # PATENT NOTICE
 * #
 * # This software is distributed under the BSD 2-clause License (see LICENSE
 * # file).  This BSD License does not make any patent claims and as such, does
 * # not act as a patent grant.  The purpose of this section is for each contributor
 * # to define their intentions with respect to intellectual property.
 * #
 * # Each contributor to this source code is encouraged to state their patent
 * # claims and licensing mechanisms for any contributions made. At the end of
 * # this section contributors may each make their own statements.  Contributor's
 * # claims and grants only apply to the pieces (source code, programs, text,
 * # media, etc) that they have contributed directly to this software.
 * #
 * # There is no guarantee that this section is complete, up to date or accurate. It
 * # is up to the contributors to maintain their portion of this section and up to
 * # the user of the software to verify any claims herein.
 * #
 * # Do not remove this header notification.  The contents of this section must be
 * # present in all distributions of the software.  You may only modify your own
 * # intellectual property statements.  Please provide contact information.
 *
 * - Palo Alto Research Center, Inc
 * This software distribution does not grant any rights to patents owned by Palo
 * Alto Research Center, Inc (PARC). Rights to these patents are available via
 * various mechanisms. As of January 2016 PARC has committed to FRAND licensing any
 * intellectual property used by its contributions to this software. You may
 * contact PARC at cipo@parc.com for more information or visit http://www.ccnx.org
 */


#ifndef CCNS3SIM_MODEL_NODE_CCNX_ROUTE_ENTRY_H_
#define CCNS3SIM_MODEL_NODE_CCNX_ROUTE_ENTRY_H_

#include "ns3/simple-ref-count.h"
#include "ns3/ccnx-name.h"
#include "ns3/ccnx-connection.h"

namespace ns3 {
namespace ccnx {

/**
 * @ingroup ccnx-l3
 *
 * A CCNxRouteEntry represents the data that is put in the FIB.  It is a (prefix, cost, Connection) tuple.  The prefix
 * is the CCNx name prefix.  The cost is a measure of using the route.  The Connection is the egress connection, which
 * is stored in the CCNxL3Protocol to identify neighbors.
 *
 * Note that a given prefix may have multiple CCNxRouteEntries that make up the complete route state.
 */
class CCNxRouteEntry : public SimpleRefCount<CCNxRouteEntry>
{
public:
  /**
   * Creates a route entry.  Once created, this object is immutable.
   *
   * @param [in] prefix The prefix of the route entry
   * @param [in] cost The cost of the route entry.  The routing protocol is responsible for the relative scaling of these.
   * @param [in] egressConnection The egress connection in CCNxL3Protocol to use for the nexthop.
   */
  CCNxRouteEntry (Ptr<const CCNxName> prefix, uint32_t cost, Ptr<CCNxConnection> egressConnection);

  virtual ~CCNxRouteEntry ();

  /**
   * Returns the name prefix associated with this route entry
   * @return
   */
  Ptr<const CCNxName> GetPrefix (void) const;

  /**
   * The cost of this route entry
   * @return
   */
  uint32_t GetCost (void) const;

  /**
   * The egress connection ID of this route entry
   * @return
   */
  Ptr<CCNxConnection> GetConnection (void) const;


  /**
   * Determines if two route entries are equal.  To be equal, the prefix, cost, and connection ID must all
   * be equal.
   *
   * @param [in] other The other route entry to compare
   * @return true if equal
   * @return false if not equal
   */
  bool Equals (const CCNxRouteEntry &other) const;

  friend std::ostream & operator << (std::ostream &os, const CCNxRouteEntry &entry);

private:
  Ptr<const CCNxName> m_prefix;
  uint32_t m_cost;
  Ptr<CCNxConnection> m_egressConnection;
};

}   /* namespace ccnx */
} /* namespace ns3 */

#endif /* CCNS3SIM_MODEL_NODE_CCNX_ROUTE_ENTRY_H_ */
