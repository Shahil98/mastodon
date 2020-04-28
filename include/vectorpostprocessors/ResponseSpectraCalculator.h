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

#ifndef RESPONSESPECTRACALCULATOR_H
#define RESPONSESPECTRACALCULATOR_H

// MOOSE includes
#include "GeneralVectorPostprocessor.h"

/**
 *  ResponseSpectraCalculator is a type of VectorPostprocessor that computes the
 *  response spectra (pseudo displacement, pseudo velocity and pseudo
 *  acceleration) for the given acceleration response variables.
 */

class ResponseSpectraCalculator : public GeneralVectorPostprocessor
{
public:
  static InputParameters validParams();
  ResponseSpectraCalculator(const InputParameters & parameters);
  virtual void initialSetup() override;
  virtual void initialize() override;
  virtual void execute() override;

protected:
  /// Damping ratio.
  const Real & _xi;

  /// Start frequency for the response spectra calculation. Generally about
  /// 0.01Hz for earthquakes.
  const Real & _freq_start;

  /// End frequency for the response spectra calculation. Generally about
  /// 100Hz for earthquakes.
  const Real & _freq_end;

  /// Number of frequencies for the response spectra calculation.
  const unsigned int & _freq_num;

  /// dt for response spectra calculation. This dt will also be used to
  /// regularize the acceleration response to a uniform dt before calculating
  /// the response spectra.
  const Real & _reg_dt;

  /// Reference to the frequency vector.
  VectorPostprocessorValue & _frequency;

  /// Reference to the period vector.
  VectorPostprocessorValue & _period;

  /// Vector of pointers to the vectors of spectral values.
  std::vector<VectorPostprocessorValue *> _spectrum;

  /// Acceleration histories corresponding to the variables for which,
  /// response spectra are requested.
  std::vector<VectorPostprocessorValue *> _history_acc;

  /// Vector containing the time values in the simulation.
  const VectorPostprocessorValue & _history_time;
};

#endif
