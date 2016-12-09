//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// abstract_table.h
//
// Identification: src/include/storage/abstract_table.h
//
// Copyright (c) 2015-16, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#pragma once

<<<<<<< HEAD
#include "type/types.h"
=======
>>>>>>> ce96f57... Checkpoint for the new TempTable class. This doesn't compile. Still working on refactoring the code to make it cleaner. #183
#include "common/printable.h"
#include "common/types.h"

#include <string>

namespace peloton {

namespace concurrency {
class Transaction;
}

namespace catalog {
class Manager;
class Schema;
}

namespace storage {

/**
 * Base class for all tables
 */
class AbstractTable : public Printable {
 public:
  virtual ~AbstractTable();

 protected:
  // Table constructor
  AbstractTable(oid_t table_oid, catalog::Schema *schema, bool own_schema);

 public:
  //===--------------------------------------------------------------------===//
  // TUPLE OPERATIONS
  //===--------------------------------------------------------------------===//

  // insert tuple in table. the pointer to the index entry is returned as
  // index_entry_ptr.
  virtual ItemPointer InsertTuple(const Tuple *tuple,
                                  concurrency::Transaction *transaction,
                                  ItemPointer **index_entry_ptr = nullptr) = 0;

  // designed for tables without primary key. e.g., output table used by
  // aggregate_executor.
  virtual ItemPointer InsertTuple(const Tuple *tuple) = 0;

  //===--------------------------------------------------------------------===//
  // ACCESSORS
  //===--------------------------------------------------------------------===//

  oid_t GetOid() const { return table_oid; }

  void SetSchema(catalog::Schema *given_schema) { schema = given_schema; }

  const catalog::Schema *GetSchema() const { return (schema); }

  virtual std::string GetName() const = 0;

  // Get a string representation for debugging
  virtual const std::string GetInfo() const = 0;

  //===--------------------------------------------------------------------===//
  // UTILITIES
  //===--------------------------------------------------------------------===//

  virtual bool HasPrimaryKey() const = 0;

  virtual bool HasUniqueConstraints() const = 0;

  virtual bool HasForeignKeys() const = 0;

 protected:
  //===--------------------------------------------------------------------===//
  // MEMBERS
  //===--------------------------------------------------------------------===//

  oid_t table_oid;

  // table schema
  catalog::Schema *schema;

  /**
   * @brief Should this table own the schema?
   * Usually true.
   * Will be false if the table is for intermediate results within a query,
   * where the scheme may live longer.
   */
  bool own_schema_;
};

}  // End storage namespace
}  // End peloton namespace
