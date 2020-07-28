#include "PapyrusMath.h"

static volatile float FloatMinNormal = 1.175494E-38f;
static volatile float FloatMinDenormal = 1.401298E-45f;
static bool IsFlushToZeroEnabled = static_cast<double>(FloatMinDenormal) == 0.0;

static float Epsilon = IsFlushToZeroEnabled ? FloatMinNormal : FloatMinDenormal;

#pragma region local functions

static auto _Approximately(const float a, const float b) -> bool
{
	return fabs(b - a) < std::max(0.000001f * std::max(fabs(a), fabs(b)), Epsilon * 8);
}


static auto _Clamp(const float value, const float min, const float max) -> float
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}


static auto _Clamp01(const float value) -> float
{
	if (value < 0.f)
		return 0.f;
	if (value > 1.f)
		return 1.f;
	return value;
}


static auto _Repeat(const float t, const float length) -> float
{
	return _Clamp(t - std::floor(t / length) * length, 0.0f, length);
}


static auto _DeltaAngle(const float current, const float target) -> float
{
	auto delta = _Repeat(target - current, 360.f);
	if (delta > 180.f)
		delta -= 360.f;
	return delta;
}


static auto _Sign(const float f) -> float
{
	if (f < 0.f)
		return -1.f;
	if (f > 0.f)
		return 1.f;
	return 0.f;
}


static auto _MoveTowards(const float current, const float target, const float maxDelta) -> float
{
	if (std::fabs(target - current) <= maxDelta)
		return target;
	return current + _Sign(target - current) * maxDelta;
}

#pragma endregion

# pragma region std functions exposed to papyrus

auto papyrusMath::Abs(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> float
{
	return std::fabs(f);
}


auto papyrusMath::Acos(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> float
{
	return std::acosf(f);
}


auto papyrusMath::Atan(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> float
{
	return std::atanf(f);
}


auto papyrusMath::Atan2(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float y, const float x) -> float
{
	return std::atan2f(y, x);
}


auto papyrusMath::Asin(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> float
{
	return std::asinf(f);
}


auto papyrusMath::Ceil(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> float
{
	return std::ceilf(f);
}


auto papyrusMath::CeilToInt(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> std::int32_t
{
	return static_cast<std::int32_t>(std::ceilf(f));
}


auto papyrusMath::Cos(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> float
{
	return std::cosf(f);
}


auto papyrusMath::Exp(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float p) -> float
{
	return std::expf(p);
}


auto papyrusMath::Floor(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> float
{
	return std::floorf(f);
}


auto papyrusMath::FloorToInt(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float a_value) -> std::int32_t
{
	return static_cast<std::int32_t>(std::floorf(a_value));
}


auto papyrusMath::IsPowerOfTwo(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const std::int32_t n) -> bool
{
	const auto u = static_cast<uint32_t>(n);
	return ((u | 0x80000000u) & u - 1u) == 0u;
}


auto papyrusMath::Max(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float x, const float y) -> float
{
	return std::fmax(x, y);
}


auto papyrusMath::Min(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float x, const float y) -> float
{
	return std::fmin(x, y);
}


auto papyrusMath::Log(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> float
{
	return std::logf(f);
}


auto papyrusMath::Log10(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> float
{
	return std::log10f(f);
}


auto papyrusMath::Pow(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f, const float p) -> float
{
	return std::powf(f, p);
}


auto papyrusMath::Round(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> float
{
	return std::roundf(f);
}


auto papyrusMath::RoundToInt(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> std::int32_t
{
	return static_cast<std::int32_t>(std::roundf(f));
}


auto papyrusMath::Sin(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> float
{
	return std::sinf(f);
}


auto papyrusMath::Sqrt(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> float
{
	return std::sqrtf(f);
}


auto papyrusMath::Tan(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> float
{
	return std::tanf(f);
}

# pragma endregion

# pragma region unity mathf functions exposed to papyrus

auto papyrusMath::Approximately(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float a, const float b) -> bool
{
	return _Approximately(a, b);
}


auto papyrusMath::Clamp(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float value, const float min, const float max) -> float
{
	return _Clamp(value, min, max);
}


auto papyrusMath::Clamp01(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float value) -> float
{
	return _Clamp01(value);
}


auto papyrusMath::ClosestPowerOfTwo(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const std::int32_t value) -> std::int32_t
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


auto papyrusMath::DeltaAngle(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float current, const float target) -> float
{
	return _DeltaAngle(current, target);
}


auto papyrusMath::IfThen(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const bool value, float t, float f) -> float
{
	return value ? t : f;
}


auto papyrusMath::InRange(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float value, const float min, const float max) -> bool
{
	return value >= min && value <= max;
}


auto papyrusMath::InverseLerp(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float a, const float b, const float value) -> float
{
	if (_Approximately(a, b))
		return 0.f;
	return _Clamp01((value - a) / (b - a));
}


auto papyrusMath::Lerp(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float a, const float b, const float t) -> float
{
	return a + (b - a) * _Clamp01(t);
}


auto papyrusMath::LerpAngle(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float a, const float b, const float t) -> float
{
	auto delta = _Repeat(b - a, 360);
	if (delta > 180)
		delta -= 360;
	return a + delta * _Clamp01(t);
}


auto papyrusMath::LerpUnclamped(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float a, const float b, const float t) -> float
{
	return a + (b - a) * t;
}


auto papyrusMath::MoveTowards(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float current, const float target, const float maxDelta) -> float
{
	return _MoveTowards(current, target, maxDelta);
}


auto papyrusMath::MoveTowardsAngle(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float current, float target, const float maxDelta) -> float
{
	const auto deltaAngle = _DeltaAngle(current, target);
	if (-maxDelta < deltaAngle && deltaAngle < maxDelta)
		return target;
	target = current + deltaAngle;
	return _MoveTowards(current, target, maxDelta);
}


auto papyrusMath::NextPowerOfTwo(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const std::int32_t n) -> std::int32_t
{
	return static_cast<std::int32_t>(std::pow(2, std::ceil(std::log2(n))));
}


auto papyrusMath::PingPong(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float t, const float length) -> float
{
	const auto _t = _Repeat(t, length * 2.f);
	return length - std::fabs(_t - length);
}


auto papyrusMath::Repeat(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float t, const float length) -> float
{
	return _Repeat(t, length);
}


auto papyrusMath::Sign(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float f) -> float
{
	return _Sign(f);
}


auto papyrusMath::SmoothStep(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float from, const float to, const float t) -> float
{
	auto _t = _Clamp01(t);
	_t = -2.F * _t * _t * _t + 3.F * _t * _t;
	return to * _t + from * (1.f - _t);
}

#pragma endregion


auto papyrusMath::RegisterFuncs(VM* a_vm) -> bool
{
	if (!a_vm)
	{
		logger::info("papyrusMath - couldn't get VMState");
		return false;
	}

	a_vm->RegisterFunction("Abs", "Mathf", Abs);
	a_vm->RegisterFunction("Acos", "Mathf", Acos);
	a_vm->RegisterFunction("Approximately", "Mathf", Approximately);
	a_vm->RegisterFunction("Asin", "Mathf", Asin);
	a_vm->RegisterFunction("Atan", "Mathf", Atan);
	a_vm->RegisterFunction("Atan2", "Mathf", Atan2);
	a_vm->RegisterFunction("Ceil", "Mathf", Ceil);
	a_vm->RegisterFunction("CeilToInt", "Mathf", CeilToInt);
	a_vm->RegisterFunction("Clamp", "Mathf", Clamp);
	a_vm->RegisterFunction("Clamp01", "Mathf", Clamp01);
	a_vm->RegisterFunction("ClosestPowerOfTwo", "Mathf", ClosestPowerOfTwo);
	// CorrelatedColorTemperatureToRGB not implemented
	a_vm->RegisterFunction("Cos", "Mathf", Cos);
	a_vm->RegisterFunction("DeltaAngle", "Mathf", DeltaAngle);
	a_vm->RegisterFunction("Exp", "Mathf", Exp);
	a_vm->RegisterFunction("Floor", "Mathf", Floor);
	a_vm->RegisterFunction("FloorToInt", "Mathf", FloorToInt);
	a_vm->RegisterFunction("IfThen", "Mathf", IfThen);
	a_vm->RegisterFunction("InRange", "Mathf", InRange);
	// GammaToLinearSpace not implemented
	a_vm->RegisterFunction("InverseLerp", "Mathf", InverseLerp);
	a_vm->RegisterFunction("IsPowerOfTwo", "Mathf", IsPowerOfTwo);
	a_vm->RegisterFunction("Lerp", "Mathf", Lerp);
	a_vm->RegisterFunction("LerpAngle", "Mathf", LerpAngle);
	a_vm->RegisterFunction("LerpUnclamped", "Mathf", LerpUnclamped);
	// LinearToGammaSpace not implemented
	a_vm->RegisterFunction("Log", "Mathf", Log);
	a_vm->RegisterFunction("Log10", "Mathf", Log10);
	a_vm->RegisterFunction("Max", "Mathf", Max);
	a_vm->RegisterFunction("Min", "Mathf", Min);
	a_vm->RegisterFunction("MoveTowards", "Mathf", MoveTowards);
	a_vm->RegisterFunction("MoveTowardsAngle", "Mathf", MoveTowardsAngle);
	a_vm->RegisterFunction("NextPowerOfTwo", "Mathf", NextPowerOfTwo);
	// PerlinNoise not implemented
	a_vm->RegisterFunction("PingPong", "Mathf", PingPong);
	a_vm->RegisterFunction("Pow", "Mathf", Pow);
	a_vm->RegisterFunction("Repeat", "Mathf", Repeat);
	a_vm->RegisterFunction("Round", "Mathf", Round);
	a_vm->RegisterFunction("RoundToInt", "Mathf", RoundToInt);
	a_vm->RegisterFunction("Sign", "Mathf", Sign);
	a_vm->RegisterFunction("Sin", "Mathf", Sin);
	// SmoothDamp not implemented
	// SmoothDampAngle not implemented
	a_vm->RegisterFunction("SmoothStep", "Mathf", SmoothStep);
	a_vm->RegisterFunction("Sqrt", "Mathf", Sqrt);
	a_vm->RegisterFunction("Tan", "Mathf", Tan);

	return true;
}
