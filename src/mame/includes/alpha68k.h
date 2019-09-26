// license:BSD-3-Clause
// copyright-holders:Pierpaolo Prazzoli, Bryan McPhail
/*************************************************************************

    SNK/Alpha 68000 based games

*************************************************************************/
#ifndef MAME_INCLUDES_ALPHA68K_H
#define MAME_INCLUDES_ALPHA68K_H

#pragma once

#include "cpu/m68000/m68000.h"
#include "cpu/mcs48/mcs48.h"
#include "cpu/z80/z80.h"
#include "sound/2203intf.h"
#include "sound/3812intf.h"
#include "sound/ay8910.h"
#include "sound/dac.h"
#include "sound/volt_reg.h"
#include "sound/ym2413.h"
#include "machine/74259.h"
#include "machine/gen_latch.h"
#include "emupal.h"
#include "screen.h"
#include "tilemap.h"
#include "speaker.h"


class alpha68k_state : public driver_device
{
public:
	alpha68k_state(const machine_config &mconfig, device_type type, const char *tag) :
		driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_audiocpu(*this, "audiocpu"),
		m_gfxdecode(*this, "gfxdecode"),
		m_screen(*this, "screen"),
		m_palette(*this, "palette"),
		m_outlatch(*this, "outlatch"),
		m_soundlatch(*this, "soundlatch"),
		m_shared_ram(*this, "shared_ram"),
		m_spriteram(*this, "spriteram"),
		m_videoram(*this, "videoram"),
		m_color_proms(*this, "color_proms"),
		m_in(*this, "IN%u", 0U),
		m_audiobank(*this, "audiobank")
	{ }

	void alpha68k_II(machine_config &config);
	void btlfieldb(machine_config &config);
	void alpha68k_II_gm(machine_config &config);
	void alpha68k_III(machine_config &config);
	void alpha68k_V(machine_config &config);
	void alpha68k_V_sb(machine_config &config);

	void init_btlfield();
	void init_goldmedl();
	void init_skyadvnt();
	void init_goldmedla();
	void init_gangwarsu();
	void init_gangwars();
	void init_timesold1();
	void init_sbasebal();
	void init_sbasebalj();
	void init_skysoldr();
	void init_skyadvntu();
	void init_btlfieldb();
	void init_timesold();

protected:
	/* devices */
	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_audiocpu;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;
	optional_device<ls259_device> m_outlatch;
	required_device<generic_latch_8_device> m_soundlatch;

	/* memory pointers */
	optional_shared_ptr<u16> m_shared_ram;
	required_shared_ptr<u16> m_spriteram;
	optional_shared_ptr<u16> m_videoram;
	
	optional_region_ptr<u8> m_color_proms;

	optional_ioport_array<7> m_in;
	optional_memory_bank m_audiobank;

	void flipscreen_w(int flip);
	u16 sound_cpu_r();
	void sound_bank_w(u8 data);

	DECLARE_MACHINE_START(common);
	DECLARE_MACHINE_RESET(common);
	DECLARE_VIDEO_START(alpha68k);

	int           m_flipscreen;

	// MCU sims
	void alpha_microcontroller_w(offs_t offset, u16 data, u16 mem_mask);
	int           m_invert_controls;
	int           m_microcontroller_id;
	unsigned      m_game_id;  // see below
	unsigned      m_deposits1;
	unsigned      m_deposits2;
	unsigned      m_credits;
	unsigned      m_coinvalue;
	int           m_coin_id;
	unsigned      m_microcontroller_data;
	unsigned      m_trigstate;
	int           m_latch;

	void set_screen_raw_params(machine_config &config);

private:
	u16 control_1_r();
	u16 control_2_r();
	u16 control_3_r();
	u16 control_4_r();
	void outlatch_w(offs_t offset, u8 data = 0);
	u16 alpha_II_trigger_r(offs_t offset);
	u16 alpha_V_trigger_r(offs_t offset);
	void porta_w(u8 data);
	void videoram_w(offs_t offset, u16 data);
	DECLARE_WRITE_LINE_MEMBER(video_control2_w);
	DECLARE_WRITE_LINE_MEMBER(video_control3_w);

	TILE_GET_INFO_MEMBER(get_tile_info);
	DECLARE_MACHINE_START(alpha68k_II);
	DECLARE_MACHINE_RESET(alpha68k_II);
	DECLARE_MACHINE_START(alpha68k_V);
	DECLARE_MACHINE_RESET(alpha68k_V);
	u32 screen_update_alpha68k_II(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	u32 screen_update_alpha68k_V(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	u32 screen_update_alpha68k_V_sb(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	INTERRUPT_GEN_MEMBER(sound_nmi);
	void video_bank_w(u8 data);
	void draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect, int j, int s, int e);
	void draw_sprites_V(bitmap_ind16 &bitmap, const rectangle &cliprect, int j, int s, int e, u16 fx_mask, u16 fy_mask, u16 sprite_mask);
	void alpha68k_II_map(address_map &map);
	void alpha68k_III_map(address_map &map);
	void alpha68k_V_map(address_map &map);
	void sound_map(address_map &map);
	void sound_portmap(address_map &map);

	u8       m_sound_nmi_mask;
	u8       m_sound_pa_latch;

	/* video-related */
	tilemap_t     *m_fix_tilemap;
	int           m_bank_base;
};

class alpha68k_prom_state : public alpha68k_state
{
public:
	alpha68k_prom_state(const machine_config &mconfig, device_type type, const char *tag)
		: alpha68k_state(mconfig, type, tag)
	{}
	
protected:	
	void palette_init(palette_device &palette) const;
};

/*
 *
 * Alpha68k N games
 *
 */
class alpha68k_N_state : public alpha68k_prom_state
{
public:
	alpha68k_N_state(const machine_config &mconfig, device_type type, const char *tag)
		: alpha68k_prom_state(mconfig, type, tag)
	{}

protected:
	void main_map(address_map &map);
	
	void base_config(machine_config &config);
	void video_config(machine_config &config, u8 tile_transchar, u8 tile_bankshift, bool is_super_stingray);
	
	void draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect, int c, int d);
	u32 screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	
	u16 kyros_alpha_trigger_r(offs_t offset);
	void sound_map(address_map &map);
	void sound_iomap(address_map &map);

private:
	u16 m_tile_transchar;
	int m_tile_bankshift;
	bool m_is_super_stingray;
};

class superstingray_state : public alpha68k_N_state
{
public:
	superstingray_state(const machine_config &mconfig, device_type type, const char *tag)
		: alpha68k_N_state(mconfig, type, tag)
	{}

	void init_sstingry();
	void sstingry(machine_config &config);

private:
	void sound_map(address_map &map);
};

class kyros_state : public alpha68k_N_state
{
public:
	kyros_state(const machine_config &mconfig, device_type type, const char *tag)
		: alpha68k_N_state(mconfig, type, tag)
	{}
	
	void kyros(machine_config &config);
	void init_kyros();
};

class jongbou_state : public alpha68k_N_state
{
public:
	jongbou_state(const machine_config &mconfig, device_type type, const char *tag)
		: alpha68k_N_state(mconfig, type, tag)
	{}
	
	void jongbou(machine_config &config);
	void init_jongbou();

private:
	void main_map(address_map &map);
	void sound_map(address_map &map);
	void sound_iomap(address_map &map);
	u16 dial_inputs_r();
};

/*
 *
 * Alpha68k I games
 *
 */
class alpha68k_I_state : public alpha68k_prom_state
{
public:
	alpha68k_I_state(const machine_config &mconfig, device_type type, const char *tag)
		: alpha68k_prom_state(mconfig, type, tag)
	{}

	
protected:
	void base_config(machine_config &config);
	void video_config(machine_config &config, int yshift);
	void draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect, int c, int d);
	u32 screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);

	int m_yshift;
};

class paddlemania_state : public alpha68k_I_state
{
public:
	paddlemania_state(const machine_config &mconfig, device_type type, const char *tag)
		: alpha68k_I_state(mconfig, type, tag)
	{}

	void paddlema(machine_config &config);
	void init_paddlema();

private:
	void main_map(address_map &map);
	void sound_map(address_map &map);
};

class thenextspace_state : public alpha68k_I_state
{
public:
	thenextspace_state(const machine_config &mconfig, device_type type, const char *tag)
		: alpha68k_I_state(mconfig, type, tag)
	{}

	void tnextspc(machine_config &config);
	void init_tnextspc();

private:
	void main_map(address_map &map);
	void sound_map(address_map &map);
	void sound_iomap(address_map &map);

	void tnextspc_coin_counters_w(offs_t offset, u16 data);
	void tnextspc_unknown_w(offs_t offset, u16 data);
	void tnextspc_soundlatch_w(u8 data);
};

/* game_id - used to deal with a few game specific situations */
enum
{
	ALPHA68K_BTLFIELDB = 1,     // used in alpha_II_trigger_r
	ALPHA68K_JONGBOU,           // used in kyros_alpha_trigger_r & kyros_draw_sprites
	ALPHA68K_KYROS          // used in kyros_draw_sprites
};

#define ALPHA68K_PLAYER_INPUT_LSB( player, button3, start, active ) \
	PORT_BIT( 0x0001, active, IPT_JOYSTICK_UP    ) PORT_PLAYER(player) \
	PORT_BIT( 0x0002, active, IPT_JOYSTICK_DOWN  ) PORT_PLAYER(player) \
	PORT_BIT( 0x0004, active, IPT_JOYSTICK_LEFT  ) PORT_PLAYER(player) \
	PORT_BIT( 0x0008, active, IPT_JOYSTICK_RIGHT ) PORT_PLAYER(player) \
	PORT_BIT( 0x0010, active, IPT_BUTTON1        ) PORT_PLAYER(player) \
	PORT_BIT( 0x0020, active, IPT_BUTTON2        ) PORT_PLAYER(player) \
	PORT_BIT( 0x0040, active, button3            ) PORT_PLAYER(player) \
	PORT_BIT( 0x0080, active, start )

#define ALPHA68K_PLAYER_INPUT_MSB( player, button3, start, active ) \
	PORT_BIT( 0x0100, active, IPT_JOYSTICK_UP    ) PORT_PLAYER(player) \
	PORT_BIT( 0x0200, active, IPT_JOYSTICK_DOWN  ) PORT_PLAYER(player) \
	PORT_BIT( 0x0400, active, IPT_JOYSTICK_LEFT  ) PORT_PLAYER(player) \
	PORT_BIT( 0x0800, active, IPT_JOYSTICK_RIGHT ) PORT_PLAYER(player) \
	PORT_BIT( 0x1000, active, IPT_BUTTON1        ) PORT_PLAYER(player) \
	PORT_BIT( 0x2000, active, IPT_BUTTON2        ) PORT_PLAYER(player) \
	PORT_BIT( 0x4000, active, button3            ) PORT_PLAYER(player) \
	PORT_BIT( 0x8000, active, start )

#define ALPHA68K_MCU \
	PORT_START("IN2")  /* Coin input to microcontroller */\
	PORT_BIT( 0x01, IP_ACTIVE_LOW, IPT_COIN1 )\
	PORT_BIT( 0x02, IP_ACTIVE_LOW, IPT_COIN2 )

// shared between skyadvnt and alpha68k_n.cpp
#define ALPHA68K_COINAGE_BITS_1TO3 \
	PORT_DIPNAME( 0x0e, 0x0e, DEF_STR( Coinage ) )  PORT_DIPLOCATION("SW1:4,5,6") \
	PORT_DIPSETTING(    0x0e, "A 1C/1C B 1C/1C" )   \
	PORT_DIPSETTING(    0x06, "A 1C/2C B 2C/1C" )   \
	PORT_DIPSETTING(    0x0a, "A 1C/3C B 3C/1C" )   \
	PORT_DIPSETTING(    0x02, "A 1C/4C B 4C/1C" )   \
	PORT_DIPSETTING(    0x0c, "A 1C/5C B 5C/1C" )   \
	PORT_DIPSETTING(    0x04, "A 1C/6C B 6C/1C" )   \
	PORT_DIPSETTING(    0x08, "A 2C/3C B 7C/1C" )   \
	PORT_DIPSETTING(    0x00, "A 3C/2C B 8C/1C" )

#endif // MAME_INCLUDES_ALPHA68K_H
