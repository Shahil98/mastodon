/*************************************************/
/*           DO NOT MODIFY THIS HEADER           */
/*                                               */
/*                     MASTODON                  */
/*                                               */
/*    (c) 2015 Battelle Energy Alliance, LLC     */
/*            ALL RIGHTS RESERVED                */
/*                                               */
/*   Prepared by Battelle Energy Alliance, LLC   */
/*     With the U. S. Department of Energy       */
/*                                               */
/*     See COPYRIGHT for full restrictions       */
/*************************************************/

#ifndef RESPONSEHISTORYBUILDER_H
#define RESPONSEHISTORYBUILDER_H

// MOOSE includes
#include "NodalVectorPostprocessor.h"

/**
 *  ResponseHistoryBuilder is a type of NodalVectorPostprocessor that builds the
 *  response histories of a nodal response such as acceleration, velocity,
 *  displacement, etc., and outputs them into a csv file.
 */
class ResponseHistoryBuilder : public NodalVectorPostprocessor
{
public:
  static InputParameters validParams();
  ResponseHistoryBuilder(const InputParameters & parameters);
  virtual void initialize() override;
  virtual void finalize() override;
  virtual void threadJoin(const UserObject & uo) override;
  virtual void execute() override;
  const std::vector<VectorPostprocessorValue *> & getHistories() const;
  const std::vector<std::string> & getHistoryNames() const;

protected:
  /// Vector containing the names of the variables where the response spectrum
  /// is requested.
  const std::vector<VariableName> & _var_names;

  /// Reference to the time vector from the analysis.
  VectorPostprocessorValue & _history_time;

  /// Vector of pointers to the response histories of different variables at the node.
  std::vector<VectorPostprocessorValue *> _history;

  /// Vector of names of VPPs output to the csv file in the same order as in _history
  std::vector<std::string> _history_names;

  /// Vector of pointers to the values of the variables at each time step.
  std::vector<const VariableValue *> _variables;

  /// Map with (key, value) = (nodeid, location of VPP in _history)
  std::map<dof_id_type, std::size_t> _node_map;

  /// Stores the data for each VPP on the current timestep
  std::vector<Real> _current_data;
};

#endif
