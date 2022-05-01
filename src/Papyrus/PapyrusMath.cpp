#pragma once

#include "PapyrusMath.h"


static volatile float FloatMinNormal = 1.175494E-38f;
static volatile float FloatMinDenormal = 1.401298E-45f;
static bool IsFlushToZeroEnabled = static_cast<double>(FloatMinDenormal) == 0.0;

static float Epsilon = IsFlushToZeroEnabled ? FloatMinNormal : FloatMinDenormal;

static auto approximately(const float a, const float b) -> bool
{
	return fabs(b - a) < std::max(0.000001f * std::max(fabs(a), fabs(b)), Epsilon * 8);
}

static auto clamp(const float value, const float min, const float max) -> float
{
	if (value < min) {
		return min;
	}
	if (value > max) {
		return max;
	}
	return value;
}

static auto clamp01(const float value) -> float
{
	if (value < 0.f) {
		return 0.f;
	}
	if (value > 1.f) {
		return 1.f;
	}
	return value;
}

static auto repeat(const float t, const float length) -> float
{
	return clamp(t - std::floor(t / length) * length, 0.0f, length);
}

static auto deltaAngle(const float current, const float target) -> float
{
	auto delta = repeat(target - current, 360.f);
	if (delta > 180.f) {
		delta -= 360.f;
	}
	return delta;
}

static auto sign(const float f) -> float
{
	if (f < 0.f) {
		return -1.f;
	}
	if (f > 0.f) {
		return 1.f;
	}
	return 0.f;
}

static auto moveTowards(const float current, const float target, const float maxDelta) -> float
{
	if (std::fabs(target - current) <= maxDelta) {
		return target;
	}
	return current + sign(target - current) * maxDelta;
}

namespace PapyrusMath
{
	auto Abs(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> float
	{
		return std::fabs(f);
	}

	auto Acos(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> float
	{
		return std::acosf(f);
	}

	auto Atan(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> float
	{
		return std::atanf(f);
	}

	auto Atan2(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float y, const float x) -> float
	{
		return std::atan2f(y, x);
	}

	auto Asin(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> float
	{
		return std::asinf(f);
	}

	auto Ceil(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> float
	{
		return std::ceilf(f);
	}

	auto CeilToInt(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> std::int32_t
	{
		return static_cast<std::int32_t>(std::ceilf(f));
	}

	auto Cos(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> float
	{
		return std::cosf(f);
	}

	auto Exp(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float p) -> float
	{
		return std::expf(p);
	}

	auto Floor(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> float
	{
		return std::floorf(f);
	}

	auto FloorToInt(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float a_value) -> std::int32_t
	{
		return static_cast<std::int32_t>(std::floorf(a_value));
	}

	auto IsPowerOfTwo(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const std::int32_t n) -> bool
	{
		const auto u = static_cast<uint32_t>(n);
		return ((u | 0x80000000u) & u - 1u) == 0u;
	}

	auto Max(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float x, const float y) -> float
	{
		return std::fmax(x, y);
	}

	auto Min(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float x, const float y) -> float
	{
		return std::fmin(x, y);
	}

	auto Log(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> float
	{
		return std::logf(f);
	}

	auto Log10(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> float
	{
		return std::log10f(f);
	}

	auto Pow(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f, const float p) -> float
	{
		return std::powf(f, p);
	}

	auto Round(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> float
	{
		return std::roundf(f);
	}

	auto RoundToInt(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> std::int32_t
	{
		return static_cast<std::int32_t>(std::roundf(f));
	}

	auto Sin(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> float
	{
		return std::sinf(f);
	}

	auto Sqrt(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> float
	{
		return std::sqrtf(f);
	}

	auto Tan(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> float
	{
		return std::tanf(f);
	}

	# pragma endregion

	# pragma region unity mathf functions exposed to papyrus

	auto Approximately(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float a, const float b) -> bool
	{
		return approximately(a, b);
	}

	auto Clamp(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float value, const float min, const float max) -> float
	{
		return clamp(value, min, max);
	}

	auto Clamp01(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float value) -> float
	{
		return clamp01(value);
	}

	auto ClosestPowerOfTwo(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const std::int32_t value) -> std::int32_t
	{
		auto v = value;

		v--;
		v |= v >> 1;
		v |= v >> 2;
		v |= v >> 4;
		v |= v >> 8;
		v |= v >> 16;
		v++;

		auto x = v >> 1;

		return v - value > value - x ? x : v;
	}

	auto DeltaAngle(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float current, const float target) -> float
	{
		return deltaAngle(current, target);
	}

	auto IfThen(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const bool value, float t, float f) -> float
	{
		return value ? t : f;
	}

	auto InRange(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float value, const float min, const float max) -> bool
	{
		return value >= min && value <= max;
	}

	auto InverseLerp(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float a, const float b, const float value) -> float
	{
		if (approximately(a, b)) {
			return 0.f;
		}
		return clamp01((value - a) / (b - a));
	}

	auto Lerp(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float a, const float b, const float t) -> float
	{
		return a + (b - a) * clamp01(t);
	}

	auto LerpAngle(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float a, const float b, const float t) -> float
	{
		auto delta = repeat(b - a, 360);
		if (delta > 180) {
			delta -= 360;
		}
		return a + delta * clamp01(t);
	}

	auto LerpUnclamped(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float a, const float b, const float t) -> float
	{
		return a + (b - a) * t;
	}

	auto MoveTowards(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float current, const float target, const float maxDelta) -> float
	{
		return moveTowards(current, target, maxDelta);
	}

	auto MoveTowardsAngle(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float current, float target, const float maxDelta) -> float
	{
		const auto dAngle = deltaAngle(current, target);
		if (-maxDelta < dAngle && dAngle < maxDelta) {
			return target;
		}
		target = current + dAngle;
		return moveTowards(current, target, maxDelta);
	}

	auto NextPowerOfTwo(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const std::int32_t n) -> std::int32_t
	{
		return static_cast<std::int32_t>(std::pow(2, std::ceil(std::log2(n))));
	}

	auto PingPong(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float t, const float length) -> float
	{
		const auto _t = repeat(t, length * 2.f);
		return length - std::fabs(_t - length);
	}

	auto Repeat(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float t, const float length) -> float
	{
		return repeat(t, length);
	}

	auto Sign(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> float
	{
		return sign(f);
	}

	auto SmoothStep(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float from, const float to, const float t) -> float
	{
		auto _t = clamp01(t);
		_t = -2.F * _t * _t * _t + 3.F * _t * _t;
		return to * _t + from * (1.f - _t);
	}

	auto RegisterFuncs(VM* a_vm) -> bool
	{
		if (!a_vm)
		{
			logger::info("PapyrusMath - couldn't get VMState"sv);
			return false;
		}

		a_vm->RegisterFunction("Abs"sv, PROJECT_NAME, Abs);
		a_vm->RegisterFunction("Acos"sv, PROJECT_NAME, Acos);
		a_vm->RegisterFunction("Approximately"sv, PROJECT_NAME, Approximately);
		a_vm->RegisterFunction("Asin"sv, PROJECT_NAME, Asin);
		a_vm->RegisterFunction("Atan"sv, PROJECT_NAME, Atan);
		a_vm->RegisterFunction("Atan2"sv, PROJECT_NAME, Atan2);
		a_vm->RegisterFunction("Ceil"sv, PROJECT_NAME, Ceil);
		a_vm->RegisterFunction("CeilToInt"sv, PROJECT_NAME, CeilToInt);
		a_vm->RegisterFunction("Clamp"sv, PROJECT_NAME, Clamp);
		a_vm->RegisterFunction("Clamp01"sv, PROJECT_NAME, Clamp01);
		a_vm->RegisterFunction("ClosestPowerOfTwo"sv, PROJECT_NAME, ClosestPowerOfTwo);
		// CorrelatedColorTemperatureToRGB not implemented
		a_vm->RegisterFunction("Cos"sv, PROJECT_NAME, Cos);
		a_vm->RegisterFunction("DeltaAngle"sv, PROJECT_NAME, DeltaAngle);
		a_vm->RegisterFunction("Exp"sv, PROJECT_NAME, Exp);
		a_vm->RegisterFunction("Floor"sv, PROJECT_NAME, Floor);
		a_vm->RegisterFunction("FloorToInt"sv, PROJECT_NAME, FloorToInt);
		a_vm->RegisterFunction("IfThen"sv, PROJECT_NAME, IfThen);
		a_vm->RegisterFunction("InRange"sv, PROJECT_NAME, InRange);
		// GammaToLinearSpace not implemented
		a_vm->RegisterFunction("InverseLerp"sv, PROJECT_NAME, InverseLerp);
		a_vm->RegisterFunction("IsPowerOfTwo"sv, PROJECT_NAME, IsPowerOfTwo);
		a_vm->RegisterFunction("Lerp"sv, PROJECT_NAME, Lerp);
		a_vm->RegisterFunction("LerpAngle"sv, PROJECT_NAME, LerpAngle);
		a_vm->RegisterFunction("LerpUnclamped"sv, PROJECT_NAME, LerpUnclamped);
		// LinearToGammaSpace not implemented
		a_vm->RegisterFunction("Log"sv, PROJECT_NAME, Log);
		a_vm->RegisterFunction("Log10"sv, PROJECT_NAME, Log10);
		a_vm->RegisterFunction("Max"sv, PROJECT_NAME, Max);
		a_vm->RegisterFunction("Min"sv, PROJECT_NAME, Min);
		a_vm->RegisterFunction("MoveTowards"sv, PROJECT_NAME, MoveTowards);
		a_vm->RegisterFunction("MoveTowardsAngle"sv, PROJECT_NAME, MoveTowardsAngle);
		a_vm->RegisterFunction("NextPowerOfTwo"sv, PROJECT_NAME, NextPowerOfTwo);
		// PerlinNoise not implemented
		a_vm->RegisterFunction("PingPong"sv, PROJECT_NAME, PingPong);
		a_vm->RegisterFunction("Pow"sv, PROJECT_NAME, Pow);
		a_vm->RegisterFunction("Repeat"sv, PROJECT_NAME, Repeat);
		a_vm->RegisterFunction("Round"sv, PROJECT_NAME, Round);
		a_vm->RegisterFunction("RoundToInt"sv, PROJECT_NAME, RoundToInt);
		a_vm->RegisterFunction("Sign"sv, PROJECT_NAME, Sign);
		a_vm->RegisterFunction("Sin"sv, PROJECT_NAME, Sin);
		// SmoothDamp not implemented
		// SmoothDampAngle not implemented
		a_vm->RegisterFunction("SmoothStep"sv, PROJECT_NAME, SmoothStep);
		a_vm->RegisterFunction("Sqrt"sv, PROJECT_NAME, Sqrt);
		a_vm->RegisterFunction("Tan"sv, PROJECT_NAME, Tan);

		return true;
	}
}