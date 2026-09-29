#include "module.h"

static void setParam(TModule& module, uint8_t index, const char* name, uint16_t min, uint16_t max)
{
	module.parameter[index].value = 0;
	module.parameter[index].min = min;
	module.parameter[index].max = max;
	module.parameter[index].name = name;
}

static void addParam(TModule& module, const char* name, uint16_t min = 0, uint16_t max = 127)
{
	// module.parameter array was expanded to 32 entries in preset.h
	if (module.parameterCount >= 32)
	{
		return;
	}
	setParam(module, module.parameterCount++, name, min, max);
}

static void initModuleParameters(TModule& module)
{
	module.parameterCount = 0;
	for (uint8_t i = 0; i < 32; ++i)
	{
		module.parameter[i].value = 0;
		module.parameter[i].min = 0;
		module.parameter[i].max = 127;
		module.parameter[i].name = 0;
	}
}

TModule makeEmptyModule(TModuleType type, TModuleChannel channel, uint8_t moduleId, uint8_t instanceId)
{
	TModule module;
	memset(&module, 0, sizeof(module));
	module.type = type;
	module.channel = channel;
	module.moduleId = moduleId;
	module.instaceId = instanceId;
	module.parameterCount = 0;
	return module;
}

TModule makeNoiseGateModule(uint8_t moduleId, uint8_t instanceId, TModuleChannel channel)
{
	TModule module = makeEmptyModule(NG_MODULE, channel, moduleId, instanceId);
	initModuleParameters(module);
	addParam(module, "on", 0, 1);
	addParam(module, "threshold", 0, 127);
	addParam(module, "attack", 0, 127);
	addParam(module, "decay", 0, 127);
	return module;
}

TModule makeCompressorModule(uint8_t moduleId, uint8_t instanceId, TModuleChannel channel)
{
	TModule module = makeEmptyModule(CM_MODULE, channel, moduleId, instanceId);
	initModuleParameters(module);
	addParam(module, "on", 0, 1);
	addParam(module, "threshold", 0, 127);
	addParam(module, "ratio", 0, 127);
	addParam(module, "volume", 0, 127);
	addParam(module, "attack", 0, 127);
	addParam(module, "knee", 0, 127);
	return module;
}

TModule makePreampModule(uint8_t moduleId, uint8_t instanceId, TModuleChannel channel)
{
	TModule module = makeEmptyModule(PR_MODULE, channel, moduleId, instanceId);
	initModuleParameters(module);
	addParam(module, "gain", 0, 127);
	addParam(module, "volume", 0, 127);

	addParam(module, "low_clean", 0, 127);
	addParam(module, "mid_clean", 0, 127);
	addParam(module, "high_clean", 0, 127);
	addParam(module, "low_crunch", 0, 127);
	addParam(module, "mid_crunch", 0, 127);
	addParam(module, "high_crunch", 0, 127);
	addParam(module, "low_lead", 0, 127);
	addParam(module, "mid_lead", 0, 127);
	addParam(module, "high_lead", 0, 127);
	return module;
}

TModule makeAmpModule(uint8_t moduleId, uint8_t instanceId, TModuleChannel channel)
{
	TModule module = makeEmptyModule(PA_MODULE, channel, moduleId, instanceId);
	initModuleParameters(module);
	addParam(module, "on", 0, 1);
	addParam(module, "master", 0, 127);
	addParam(module, "presence", 0, 127);
	addParam(module, "level", 0, 127);
	addParam(module, "type", 0, 14);
	return module;
}

TModule makeCabModule(uint8_t moduleId, uint8_t instanceId, TModuleChannel channel)
{
	TModule module = makeEmptyModule(IR_MODULE, channel, moduleId, instanceId);
	initModuleParameters(module);
	addParam(module, "on", 0, 1);
	addParam(module, "ir", 0, 127);
	addParam(module, "mix", 0, 127);
	return module;
}

TModule makeEqModule(uint8_t moduleId, uint8_t instanceId, TModuleChannel channel)
{
	TModule module = makeEmptyModule(EQ_MODULE, channel, moduleId, instanceId);
	initModuleParameters(module);
	addParam(module, "on", 0, 1);
	addParam(module, "gain", 0, 127);
	addParam(module, "freq", 0, 127);
	addParam(module, "q", 0, 127);
	addParam(module, "lpf", 0, 127);
	addParam(module, "hpf", 0, 127);
	addParam(module, "presence", 0, 127);
	addParam(module, "position", 0, 1);
	return module;
}

TModule makePhaserModule(uint8_t moduleId, uint8_t instanceId, TModuleChannel channel)
{
	TModule module = makeEmptyModule(PH_MODULE, channel, moduleId, instanceId);
	initModuleParameters(module);
	addParam(module, "on", 0, 1);
	addParam(module, "mix", 0, 127);
	addParam(module, "rate", 0, 127);
	addParam(module, "width", 0, 127);
	addParam(module, "center", 0, 127);
	addParam(module, "feedback", 0, 127);
	addParam(module, "stages", 0, 2);
	addParam(module, "hpf", 0, 127);
	addParam(module, "position", 0, 1);
	return module;
}

TModule makeFlangerModule(uint8_t moduleId, uint8_t instanceId, TModuleChannel channel)
{
	TModule module = makeEmptyModule(FL_MODULE, channel, moduleId, instanceId);
	initModuleParameters(module);
	addParam(module, "on", 0, 1);
	addParam(module, "mix", 0, 127);
	addParam(module, "genType", 0, 2);
	addParam(module, "rate", 0, 127);
	addParam(module, "width", 0, 127);
	addParam(module, "delay", 0, 127);
	addParam(module, "feedback", 0, 127);
	addParam(module, "hpf", 0, 127);
	addParam(module, "position", 0, 1);
	return module;
}

TModule makeReverbModule(uint8_t moduleId, uint8_t instanceId, TModuleChannel channel)
{
	TModule module = makeEmptyModule(RV_MODULE, channel, moduleId, instanceId);
	initModuleParameters(module);
	addParam(module, "on", 0, 1);
	addParam(module, "mix", 0, 127);
	addParam(module, "type", 0, 6);
	addParam(module, "time", 0, 127);
	addParam(module, "size", 0, 127);
	addParam(module, "damping", 0, 127);
	addParam(module, "hpf", 0, 127);
	addParam(module, "lpf", 0, 127);
	addParam(module, "detune", 0, 127);
	addParam(module, "diffusion", 0, 127);
	addParam(module, "predelay", 0, 127);
	addParam(module, "tail", 0, 127);
	return module;
}

TModule makeDelayModule(uint8_t moduleId, uint8_t instanceId, TModuleChannel channel)
{
	TModule module = makeEmptyModule(DL_MODULE, channel, moduleId, instanceId);
	initModuleParameters(module);
	addParam(module, "on", 0, 1);
	addParam(module, "mix", 0, 127);
	addParam(module, "feedback", 0, 127);
	addParam(module, "lpf", 0, 127);
	addParam(module, "hpf", 0, 127);
	addParam(module, "pan1", 0, 127);
	addParam(module, "volume2", 0, 127);
	addParam(module, "pan2", 0, 127);
	addParam(module, "offset", 0, 127);
	addParam(module, "modulation", 0, 127);
	addParam(module, "rate", 0, 127);
	addParam(module, "direction", 0, 1);
	addParam(module, "tap", 0, 5);
	addParam(module, "tail", 0, 127);
	return module;
}

TPreampModule makePreampModuleState(void)
{
	TPreampModule state;
	memset(&state, 0, sizeof(state));
	state.gain_clean = 0;
	state.gain_crunch = 0;
	state.gain_lead = 0;
	state.volume_clean = 0;
	state.volume_crunch = 0;
	state.volume_lead = 0;
	state.low_clean = 0;
	state.mid_clean = 0;
	state.high_clean = 0;
	state.low_crunch = 0;
	state.mid_crunch = 0;
	state.high_crunch = 0;
	state.low_lead = 0;
	state.mid_lead = 0;
	state.high_lead = 0;
	return state;
}

static uint16_t preamp_current_vals[5]; // gain, volume, low, mid, high

void preampChangeType(TModule& module, const TPreampModule& state, uint8_t type)
{
	// Map type to values: 0/1 -> clean, 2 -> crunch(od), 3 -> lead
	uint8_t gain = 0;
	uint8_t volume = 0;
	uint8_t low = 0, mid = 0, high = 0;

	switch (type)
	{
	case 2: // crunch/od
		gain = state.gain_crunch;
		volume = state.volume_crunch;
		low = state.low_crunch;
		mid = state.mid_crunch;
		high = state.high_crunch;
		break;
	case 3: // lead
		gain = state.gain_lead;
		volume = state.volume_lead;
		low = state.low_lead;
		mid = state.mid_lead;
		high = state.high_lead;
		break;
	case 0:
	case 1:
	default: // clean / default
		gain = state.gain_clean;
		volume = state.volume_clean;
		low = state.low_clean;
		mid = state.mid_clean;
		high = state.high_clean;
		break;
	}

	preamp_current_vals[0] = gain;
	preamp_current_vals[1] = volume;
	preamp_current_vals[2] = low;
	preamp_current_vals[3] = mid;
	preamp_current_vals[4] = high;

	// If module has parameters, point the first five (gain, volume, low, mid, high) to our current values
//	if (module.parameterCount >= 1) module.parameter[0].ptr = &preamp_current_vals[0];
//	if (module.parameterCount >= 2) module.parameter[1].ptr = &preamp_current_vals[1];
//	if (module.parameterCount >= 3) module.parameter[2].ptr = &preamp_current_vals[2];
//	if (module.parameterCount >= 4) module.parameter[3].ptr = &preamp_current_vals[3];
//	if (module.parameterCount >= 5) module.parameter[4].ptr = &preamp_current_vals[4];
}
