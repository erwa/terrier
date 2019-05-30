#pragma once

#include <string>
#include <unordered_map>

#include "traffic_cop/portal.h"
#include "traffic_cop/statement.h"

namespace terrier::network {

/**
 * A ConnectionContext stores the state of a connection.
 */

struct ConnectionContext {
  /**
   * The statements in this connection
   */
  std::unordered_map<std::string, traffic_cop::Statement> statements;

  /**
   * The portals in this connection
   */
  std::unordered_map<std::string, traffic_cop::Portal> portals;

  /**
   * Cleans up this ConnectionContext.
   * This is called when its connection handle is reused to occupy another connection or destroyed.
   */
  void Reset() {
    // Cleans up all the sqlite statements in this connection
    for (auto pair : statements) pair.second.Finalize();

    statements.clear();
    portals.clear();
  }
};

}  // namespace terrier::network
