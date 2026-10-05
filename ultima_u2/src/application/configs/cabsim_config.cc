#include "cabsim_config.h"

#include <string.h>

#include "processing/audio_process.h"
#include "processing/compressor.h"
#include "module.h"

static void setParameterValue(TModuleDescriptor& module, uint8_t index, int16_t value)
{
	if (index >= module.parameterCount)
	{
		return;
	}
	module.parameter[index].value = value;
}

static void applyPreampValues(TModuleDescriptor& module, const TCabsimConfig& config)
{
	setParameterValue(module, 0, config.preamp_vol);
	setParameterValue(module, 1, config.preamp_vol);
	setParameterValue(module, 2, config.preamp_lo);
	setParameterValue(module, 3, config.preamp_mi);
	setParameterValue(module, 4, config.preamp_hi);
	setParameterValue(module, 5, config.preamp_lo);
	setParameterValue(module, 6, config.preamp_mi);
	setParameterValue(module, 7, config.preamp_hi);
	setParameterValue(module, 8, config.preamp_lo);
	setParameterValue(module, 9, config.preamp_mi);
	setParameterValue(module, 10, config.preamp_hi);
	setParameterValue(module, 11, config.preamp_pos);
}

static void applyAmpValues(TModuleDescriptor& module, const TCabsimConfig& config)
{
	setParameterValue(module, 0, config.amp_on ? 1 : 0);
	setParameterValue(module, 1, config.a_vol);
	setParameterValue(module, 2, config.presen_vol);
	setParameterValue(module, 3, config.amp_slave);
	setParameterValue(module, 4, config.a_t);
}

static void applyCabValues(TModuleDescriptor& module, const TCabsimConfig& config)
{
	setParameterValue(module, 0, config.cab_on ? 1 : 0);
	setParameterValue(module, 1, config.ir_mix);
	setParameterValue(module, 2, config.cab_vol);
}

static void applyEqValues(TModuleDescriptor& module, const TCabsimConfig& config)
{
	setParameterValue(module, 0, config.eq_on ? 1 : 0);
	setParameterValue(module, 1, config.eq1);
	setParameterValue(module, 2, config.eq2);
	setParameterValue(module, 3, config.eq3);
	setParameterValue(module, 4, config.eq4);
	setParameterValue(module, 5, config.eq5);
	setParameterValue(module, 6, config.q1);
	setParameterValue(module, 7, config.q2);
	setParameterValue(module, 8, config.q3);
	setParameterValue(module, 9, config.q4);
	setParameterValue(module, 10, config.q5);
	setParameterValue(module, 11, config.preamp_pos);
}

static void applyNoiseGateValues(TModuleDescriptor& module, const TCabsimConfig& config)
{
	setParameterValue(module, 0, config.Ng ? 1 : 0);
	setParameterValue(module, 1, config.Ng_th);
	setParameterValue(module, 2, config.ga_at);
	setParameterValue(module, 3, config.ga_de);
}

static void applyCompressorValues(TModuleDescriptor& module, const TCabsimConfig& config)
{
	setParameterValue(module, 0, config.compr_on ? 1 : 0);
	setParameterValue(module, 1, config.c_thr);
	setParameterValue(module, 2, config.c_rat);
	setParameterValue(module, 3, config.c_vol);
	setParameterValue(module, 4, config.c_at);
	setParameterValue(module, 5, config.c_rel);
}

static void applyReverbValues(TModuleDescriptor& module, const TCabsimConfig& config)
{
	setParameterValue(module, 0, config.r_vol ? 1 : 0);
	setParameterValue(module, 1, config.r_vol);
	setParameterValue(module, 2, config.r_typ);
	setParameterValue(module, 3, config.r_time);
	setParameterValue(module, 4, config.r_size);
	setParameterValue(module, 5, config.r_dump);
	setParameterValue(module, 6, config.r_lp);
	setParameterValue(module, 7, config.r_hp);
	setParameterValue(module, 8, config.r_det);
	setParameterValue(module, 9, config.r_diff);
	setParameterValue(module, 10, config.r_pre);
	setParameterValue(module, 11, config.rev_tail);
}

static void applyDelayValues(TModuleDescriptor& module, const TCabsimConfig& config)
{
	setParameterValue(module, 0, config.d_vol ? 1 : 0);
	setParameterValue(module, 1, config.d_vol);
	setParameterValue(module, 2, config.d_fed);
	setParameterValue(module, 3, config.d_lp);
	setParameterValue(module, 4, config.d_hp);
	setParameterValue(module, 5, config.d_pan);
	setParameterValue(module, 6, config.dp_vol);
	setParameterValue(module, 7, config.dp_pan);
	setParameterValue(module, 8, config.dp_d);
	setParameterValue(module, 9, config.d_mod);
	setParameterValue(module, 10, config.d_ra);
	setParameterValue(module, 11, config.d_dir);
	setParameterValue(module, 12, config.d_tim_hi);
	setParameterValue(module, 13, config.d_tim_lo);
	setParameterValue(module, 14, config.d_tap_t);
	setParameterValue(module, 15, config.d_tail);
}

static void applyPhaserValues(TModuleDescriptor& module, const TCabsimConfig& config)
{
	setParameterValue(module, 0, config.phaz_on ? 1 : 0);
	setParameterValue(module, 1, config.ph_mix);
	setParameterValue(module, 2, config.ph_rate);
	setParameterValue(module, 3, config.ph_cent);
	setParameterValue(module, 4, config.ph_width);
	setParameterValue(module, 5, config.ph_fb);
	setParameterValue(module, 6, config.ph_stag);
	setParameterValue(module, 7, config.ph_hpf);
	setParameterValue(module, 8, config.ph_poz);
}

static void applyFlangerValues(TModuleDescriptor& module, const TCabsimConfig& config)
{
	setParameterValue(module, 0, config.flan_on ? 1 : 0);
	setParameterValue(module, 1, config.fl_mix);
	setParameterValue(module, 2, config.fl_lfo);
	setParameterValue(module, 3, config.fl_rat);
	setParameterValue(module, 4, config.fl_widt);
	setParameterValue(module, 5, config.fl_del);
	setParameterValue(module, 6, config.fl_fb);
	setParameterValue(module, 7, config.fl_hpf);
	setParameterValue(module, 8, config.fl_poz);
}

static void addModule(TPreset& preset, const TModuleDescriptor& module)
{
	if (preset.moduleCount >= 16)
	{
		return;
	}

	preset.module[preset.moduleCount++] = module;
}

static void addPreampVariant(TPreset& preset, uint8_t moduleId, uint8_t instanceId, TModuleChannel channel, const TCabsimConfig& config)
{
	TModuleDescriptor preamp = makePreampModule(moduleId, instanceId, channel);
	if (config.preamp_vol == 0)
	{
		preamp.parameterCount = 3;
	}
	else if (config.preamp_vol == 1)
	{
		preamp.parameterCount = 6;
	}
	else if (config.preamp_vol == 2)
	{
		preamp.parameterCount = 9;
	}
	else if (config.preamp_vol == 3)
	{
		preamp.parameterCount = 12;
	}
	applyPreampValues(preamp, config);
	addModule(preset, preamp);
}

static void addAmp(TPreset& preset, uint8_t moduleId, const TCabsimConfig& config)
{
	TModuleDescriptor amp = makeAmpModule(moduleId, 0, MONO_CHANNEL);
	applyAmpValues(amp, config);
	addModule(preset, amp);
}

static void addCab(TPreset& preset, uint8_t moduleId, const TCabsimConfig& config)
{
	TModuleDescriptor cab = makeCabModule(moduleId, 0, MONO_CHANNEL);
	applyCabValues(cab, config);
	addModule(preset, cab);
}

static void addEq(TPreset& preset, uint8_t moduleId, const TCabsimConfig& config)
{
	TModuleDescriptor eq = makeEqModule(moduleId, 0, MONO_CHANNEL);
	applyEqValues(eq, config);
	addModule(preset, eq);
}

static void addNoiseGate(TPreset& preset, uint8_t moduleId, const TCabsimConfig& config)
{
	TModuleDescriptor gate = makeNoiseGateModule(moduleId, 0, MONO_CHANNEL);
	applyNoiseGateValues(gate, config);
	addModule(preset, gate);
}

extern Compressor compr;
static void addCompressor(TPreset& preset, uint8_t moduleId, const TCabsimConfig& config)
{
	TModuleDescriptor comp = makeCompressorModule(moduleId, 0, MONO_CHANNEL);
	applyCompressorValues(comp, config);
	addModule(preset, comp);

	moduleRuntime[moduleId].stage = &compr;
	moduleRuntime[moduleId].descriptor = &preset.module[moduleId];
	moduleRuntime[moduleId].dirty = true;
}

static void addReverb(TPreset& preset, uint8_t moduleId, const TCabsimConfig& config)
{
	TModuleDescriptor rev = makeReverbModule(moduleId, 0, MONO_CHANNEL);
	applyReverbValues(rev, config);
	addModule(preset, rev);
}

static void addDelay(TPreset& preset, uint8_t moduleId, const TCabsimConfig& config)
{
	TModuleDescriptor del = makeDelayModule(moduleId, 0, MONO_CHANNEL);
	applyDelayValues(del, config);
	addModule(preset, del);
}

static void addPhaser(TPreset& preset, uint8_t moduleId, const TCabsimConfig& config)
{
	TModuleDescriptor phase = makePhaserModule(moduleId, 0, MONO_CHANNEL);
	applyPhaserValues(phase, config);
	addModule(preset, phase);
}

static void addFlanger(TPreset& preset, uint8_t moduleId, const TCabsimConfig& config)
{
	TModuleDescriptor fl = makeFlangerModule(moduleId, 0, MONO_CHANNEL);
	applyFlangerValues(fl, config);
	addModule(preset, fl);
}

TPreset makePresetFromCabsimConfig(const TCabsimConfig& config)
{
	TPreset preset;
	memset(&preset, 0, sizeof(preset));

	strncpy(preset.name, "CabSim", sizeof(preset.name) - 1);
	strncpy(preset.author, "AMT", sizeof(preset.author) - 1);
	preset.moduleCount = 0;

	uint8_t moduleId = 0;

	for(uint8_t i=0; i<MAX_PRESET_MODULES; i++)
	{
		moduleRuntime[i].stage = nullptr;
		moduleRuntime[i].descriptor = nullptr;
		moduleRuntime[i].dirty = false;
	}

	addNoiseGate(preset, moduleId++, config);
	addCompressor(preset, moduleId++, config);
	addPhaser(preset, moduleId++, config);
	addFlanger(preset, moduleId++, config);
	addPreampVariant(preset, moduleId++, 0, MONO_CHANNEL, config);
	addAmp(preset, moduleId++, config);
	addCab(preset, moduleId++, config);
	addEq(preset, moduleId++, config);
	// Filters

	// Effects in one module
	addReverb(preset, moduleId++, config);
	addDelay(preset, moduleId++, config);

	preset.moduleCount = moduleId;
	return preset;
}
