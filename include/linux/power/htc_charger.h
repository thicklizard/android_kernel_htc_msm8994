/*
 * Copyright (C) 2007 HTC Incorporated
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#ifndef __HTC_CHARGER_H__
#define __HTC_CHARGER_H__


enum htc_charger_event {
	HTC_CHARGER_EVENT_READY = 0,
	HTC_CHARGER_EVENT_VBUS_OUT,
	HTC_CHARGER_EVENT_VBUS_IN,
	HTC_CHARGER_EVENT_SRC_NONE,
	HTC_CHARGER_EVENT_SRC_USB,
	HTC_CHARGER_EVENT_SRC_AC,
	HTC_CHARGER_EVENT_SRC_WIRELESS,
	HTC_CHARGER_EVENT_OVP,
	HTC_CHARGER_EVENT_OVP_RESOLVE,
	HTC_CHARGER_EVENT_SRC_MHL_AC,
	HTC_CHARGER_EVENT_SRC_INTERNAL,
	HTC_CHARGER_EVENT_SRC_CLEAR,
	HTC_CHARGER_EVENT_SRC_DETECTING,
	HTC_CHARGER_EVENT_SRC_UNKNOWN_USB,
	HTC_CHARGER_EVENT_SRC_UNDER_RATING,
	HTC_CHARGER_EVENT_SAFETY_TIMEOUT,
	HTC_CHARGER_EVENT_BATT_UEVENT_CHANGE,
    HTC_CHARGER_EVENT_SRC_CABLE_INSERT_NOTIFY,
	HTC_CHARGER_EVENT_SRC_MHL_UNKNOWN,
	HTC_CHARGER_EVENT_SRC_MHL_100MA,
	HTC_CHARGER_EVENT_SRC_MHL_500MA,
	HTC_CHARGER_EVENT_SRC_MHL_900MA,
	HTC_CHARGER_EVENT_SRC_MHL_1500MA,
	HTC_CHARGER_EVENT_SRC_MHL_2000MA,
};

enum htc_charging_cfg {
	HTC_CHARGER_CFG_LIMIT = 0,	
	HTC_CHARGER_CFG_SLOW,
	HTC_CHARGER_CFG_FAST,
};

enum htc_power_source_type {
	
	
	HTC_PWR_SOURCE_TYPE_BATT = 0,
	HTC_PWR_SOURCE_TYPE_USB,
	HTC_PWR_SOURCE_TYPE_AC,
	HTC_PWR_SOURCE_TYPE_9VAC,
	HTC_PWR_SOURCE_TYPE_WIRELESS,
	HTC_PWR_SOURCE_TYPE_MHL_AC,
	HTC_PWR_SOURCE_TYPE_DETECTING,
	HTC_PWR_SOURCE_TYPE_UNKNOWN_USB,
	HTC_PWR_SOURCE_TYPE_PQM_FASTCHARGE,
	HTC_PWR_SOURCE_TYPE_MHL_UNKNOWN,
	HTC_PWR_SOURCE_TYPE_MHL_100MA,
	HTC_PWR_SOURCE_TYPE_MHL_500MA,
	HTC_PWR_SOURCE_TYPE_MHL_900MA,
	HTC_PWR_SOURCE_TYPE_MHL_1500MA,
	HTC_PWR_SOURCE_TYPE_MHL_2000MA,
	HTC_PWR_SOURCE_TYPE_MAX = 255,
};

enum htc_extchg_event_type {
	HTC_EXTCHG_EVENT_TYPE_TEMP_NORMAL = 1,
	HTC_EXTCHG_EVENT_TYPE_TEMP_WARM,
	HTC_EXTCHG_EVENT_TYPE_TEMP_COOL,
	HTC_EXTCHG_EVENT_TYPE_TEMP_HOT,
	HTC_EXTCHG_EVENT_TYPE_TEMP_COLD,
	HTC_EXTCHG_EVENT_TYPE_EOC_START_CHARGE,
	HTC_EXTCHG_EVENT_TYPE_EOC_STOP_CHARGE,
	HTC_EXTCHG_EVENT_TYPE_MAX = 255,
};

enum htc_ftm_power_source_type {
	HTC_FTM_PWR_SOURCE_TYPE_NONE_STOP = -1,
	HTC_FTM_PWR_SOURCE_TYPE_NONE = 0,
	HTC_FTM_PWR_SOURCE_TYPE_USB,
	HTC_FTM_PWR_SOURCE_TYPE_AC,
	HTC_FTM_PWR_SOURCE_TYPE_MAX = 255,
};

enum usb_connect_type {
	CONNECT_TYPE_MHL_UNKNOWN = -4,
	CONNECT_TYPE_NOTIFY = -3,
	CONNECT_TYPE_CLEAR = -2,
	CONNECT_TYPE_UNKNOWN = -1,
	CONNECT_TYPE_NONE = 0,
	CONNECT_TYPE_USB,
	CONNECT_TYPE_AC,
	CONNECT_TYPE_9V_AC,
	CONNECT_TYPE_WIRELESS,
	CONNECT_TYPE_INTERNAL,
	CONNECT_TYPE_UNSUPPORTED,
#ifdef CONFIG_MACH_VERDI_LTE
	
	CONNECT_TYPE_USB_9V_AC,
#endif
	CONNECT_TYPE_MHL_AC,
	CONNECT_TYPE_MHL_100MA,
	CONNECT_TYPE_MHL_500MA,
	CONNECT_TYPE_MHL_900MA,
	CONNECT_TYPE_MHL_1500MA,
	CONNECT_TYPE_MHL_2000MA,
};
struct t_usb_status_notifier{
	struct list_head notifier_link;
	const char *name;
	void (*func)(int cable_type);
};
int htc_usb_register_notifier(struct t_usb_status_notifier *notifer);
int64_t htc_qpnp_adc_get_usbid_adc(void);
int usb_get_connect_type(void);
static LIST_HEAD(g_lh_usb_notifier_list);

struct t_cable_status_notifier{
	struct list_head cable_notifier_link;
	const char *name;
	void (*func)(int cable_type);
};
int cable_detect_register_notifier(struct t_cable_status_notifier *);
static LIST_HEAD(g_lh_calbe_detect_notifier_list);

struct htc_charger {
	const char *name;
	int ready;
	int sw_safetytimer;
	int (*get_charging_source)(int *result);
	int (*get_charging_enabled)(int *result);
	int (*event_notify)(enum htc_extchg_event_type etype);
	int (*set_charger_enable)(bool enable);
	int (*set_pwrsrc_enable)(bool enable);
	int (*set_pwrsrc_and_charger_enable)
			(enum htc_power_source_type src,
			 bool chg_enable, bool pwrsrc_enable);
#ifdef CONFIG_DUTY_CYCLE_LIMIT
	int (*set_limit_charge_enable)
			(int chg_limit_reason,
			 int chg_limit_timer_sub_mask,
			 int limit_charge_timer_ma);
#else
	int (*set_limit_charge_enable)(bool enable, int reason, int restrict);
#endif
	int (*set_limit_input_current)(bool enable, int reason);
	int (*set_chg_iusbmax)(int val);
	int (*set_chg_curr_settled)(int val);
	int (*set_chg_vin_min)(int val);
	int (*toggle_charger)(void);
	int (*is_ovp)(int *result);
	int (*is_batt_temp_fault_disable_chg)(int *result);
	int (*charger_change_notifier_register)
			(struct t_cable_status_notifier *notifier);
	int (*max_input_current)(int target_ma);
	int (*dump_all)(void);
	int (*is_charging_enabled)(int *result);
	int (*is_under_rating)(int *result);
	int (*get_attr_text)(char *buf, int size);
	int (*enable_5v_output)(bool enable);
	int (*is_safty_timer_timeout)(int *result);
	int (*is_battery_full_eoc_stop)(int *result);
	int (*get_charge_type)(void);
	int (*get_chg_usb_iusbmax)(void);
	int (*get_chg_curr_settled)(void);
	int (*get_chg_vinmin)(void);
	int (*get_input_voltage_regulation)(void);
	int (*store_battery_charger_data)(void);
	int (*set_ftm_charge_enable_type)(enum htc_ftm_power_source_type ftm_src);
	int (*set_safety_timer_disable)(int disable);
	int (*is_charger_error_handle)(void);
	int (*is_cable_exist_check)(void);
	int (*usbin_mode_charge)(void);
	int (*fake_chg_src_detect)(void);
	int (*calc_max_flash_current)(void);
	int (*get_cable_type_by_usb_detect)(int *result);
	int (*prepare_suspend)(void);
	int (*complete_resume)(void);
};

int htc_charger_event_notify(enum htc_charger_event);
int usb_type_event_notify(int result);

#endif
