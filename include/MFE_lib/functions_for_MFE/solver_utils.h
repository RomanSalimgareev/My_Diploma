// This file is used in the dinamic_solver files.
// This file contains various get, set, && bool expression functions
// for checking conditions in dinamic_solver files.
#ifndef GET_SET_CONDIDION_H
#define GET_SET_CONDIDION_H

#include <array>

#include "initial_conditions.h"

namespace MFE
{
	constexpr Real PI = 3.14159265358979323846;
	constexpr Real NORMAL_REACTION_FREE = 400.0;
	constexpr Real NORMAL_REACTION_DRIVE = 100.0;
	constexpr Real EPS = 1.0e-4;
	constexpr bool HAS_DRIVE_FORCE_DRY = true;
	constexpr bool NO_DRIVE_FORCE_DRY = !HAS_DRIVE_FORCE_DRY;
	constexpr bool DRIVE_FORCE_DRY = true;
	constexpr bool DRIVE_FORCE_NO_DRY = !DRIVE_FORCE_DRY;
	constexpr std::array<UnsignedType, 4> ACTIVE_INDICES = { 0, 1, 4, 6 };
	constexpr std::array<UnsignedType, 8> INDICES_NORMAL_REACTION =
	{ 4, 7, 14, 16, 17, 19, 20, 23 };

	// The function of obtaining the amplitude of the driving force for dry
	// friction && viscous.
	// For dry, the default is 600, for viscous 220
	Real getAmplitudeForce(const bool& isDriveForceDry);

	// The function of obtaining the average velocity from the velocity vector
	// of the degrees of freedom of the nodes of interest
	Real getAveragePointsSpeed(RealVector speed);

	// The function of obtaining the coefficient of friction depending on the
	// average speed: either the coefficient of friction at rest, if the speed
	// is less than eps, || the coefficient of friction sliding, if the speed
	// is greater than eps.
	Real getCoeffDryFriction(const Real& coeffDryFrictionRest,
		const Real& coeffDryFrictionSliding,
		const Real averagePointsSpeed);

	// The function of obtaining the elastic force of the degrees of freedom of
	// the nodes of interest by displacement && stiffness matrix (analogous to
	// the stiffness of a spring).
	Real getElasticForce(const RealVector& displacement,
		const RealMatrix& matrixStiffness);

	// The function of obtaining the frequency of the driving force depending on
	// friction is either dry || viscous.
	// For dry, the default is PI, for viscous 2 * PI
	Real getFrequencyForce(const bool& isDriveForceDry);

	// The function choice of the solver depending on the friction: 1 - dry friction 
	// without a driving force; 2 - dry friction with a driving force;
	// 3 - viscous friction with a driving force.
	UnsignedType getFrictionMode();

	// The amplitude distribution function across nodes 
	// (degrees of freedom in the direction of motion).
	Real getNodeLoad(const Real& amplitudeForce);

	// The function of obtaining a normal reaction, depending on the task,
	// is dry friction without forcing || dry friction with a forcing force.
	// For friction without a driving force, the normal wall response is
	// NORMAL_REACTION_FREE by default,
	// with a driving force NORMAL_REACTION_DRIVE
	Real getNormReaction(const bool& isDriveForce);

	// The function returns the sign of the friction force in a problem with
	// a driving force depending on the average velocity ||, if the velocity is
	// less than EPS, then on the direction of the resulting force projected on ksi.
	Real getSignFrictionDrive(const Real& elasticForce,
		const Real& averagePointsSpeed, const Real& driveForce);

	// The function returns the sign of the friction force in a problem without
	// a driving force depending on the average velocity ||, if the velocity is
	// less than EPS, then on the direction of the resulting force projected on ksi.
	Real getSignFrictionFree(const Real& elasticForce,
		const Real& averagePointsSpeed);

	// The function returns the total dry friction force across the nodes.
	Real getSumFrictionForce(const RealVector& force);


	// Setting the normal reaction at the nodes (corresponding to degrees of freedom)
	// affected by the normal reaction from the walls
	void setForceNormReaction(RealVector& force,
		const bool& isDriveForce);

	// Setting the friction force at the nodes(degrees of freedom in the direction
	// of motion) for the problem of dry friction without a driving force
	void setForceDry(const Real& elasticForce,
		const Real& coeffDryFrictionRest,
		const Real& coeffDryFrictionSliding, const Real averagePointsSpeed,
		RealVector& force);

	// Setting the driving force && the friction force at the nodes (degrees 
	// of freedom in the direction of motion) for the dry friction problem
	void setForceDriveDry(const Real& signForce,
		const Real& coeffDryFrictionRest,
		const Real& coeffDryFrictionSliding, const Real averagePointsSpeed,
		const Real& driveForceNode, RealVector& force);

	// Setting the driving force by nodes (degrees of freedom in the direction
	// of motion) for the viscous friction problem
	void setForceViscous(const Real& nodeLoad, const Real& frequency,
		const Real& sumSteps, RealVector& force);


	// Checking that the sum of the elastic force && the driving force is less
	// than the friction force.
	// The driving force is co - directional with the elastic force,
	// && the friction force is opposite.
	bool isLowDriveElastic(const Real& elasticForce,
		const Real& driveForceNode, const Real& frictionForce);

	// Checking that the driving force is less than the sum of the friction force
	// && the elastic force
	// The elastic force && the friction force are co-directional,
	// while the driving force is opposite.
	bool isLowDriveForce(const Real& elasticForce,
		const Real& driveForceNode, const Real& frictionForce,
		const Real& signForce);

	// Checking that the elastic force is less than the sum of the friction
	// force && the forcing force.
	// The driving force && the friction force are co-directional,
	// while the elastic force is opposite.
	bool isLowElasticForce(const Real& elasticForce,
		const Real& driveForceNode, const Real& frictionForce,
		const Real& signForce);

	// Checking that the speed of the element is less than EPS
	bool isLowSpeedElement(const Real& averagePointsSpeedOld,
		const Real& averagePointsSpeed, const Real& averagePointsSpeedNew);

	// Checking that the elastic force && the driving force are aligned
	bool isOneWayElasticDrive(const Real& elasticForce,
		const Real& driveForceNode, const Real& signForce);

}

#endif