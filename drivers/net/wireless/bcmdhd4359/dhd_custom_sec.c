/*
 * Customer HW 4 dependant file
 *
 * Copyright (C) 1999-2016, Broadcom Corporation
 * 
 *      Unless you and Broadcom execute a separate written software license
 * agreement governing use of this software, this software is licensed to you
 * under the terms of the GNU General Public License version 2 (the "GPL"),
 * available at http://www.broadcom.com/licenses/GPLv2.php, with the
 * following added to such license:
 * 
 *      As a special exception, the copyright holders of this software give you
 * permission to link this software with independent modules, and to copy and
 * distribute the resulting executable under terms of your choice, provided that
 * you also meet, for each linked independent module, the terms and conditions of
 * the license of that module.  An independent module is a module which is not
 * derived from this software.  The special exception does not apply to any
 * modifications of the software.
 * 
 *      Notwithstanding the above, under no circumstances may you combine this
 * software in any way with any other Broadcom software provided under a license
 * other than the GPL, without Broadcom's express prior written consent.
 *
 *
 * <<Broadcom-WL-IPTag/Open:>>
 *
 * $Id: dhd_custom_sec.c 334946 2012-05-24 20:38:00Z $
 */
#if defined(CUSTOMER_HW4) || defined(CUSTOMER_HW40)
#include <typedefs.h>
#include <linuxver.h>
#include <osl.h>

#include <proto/ethernet.h>
#include <dngl_stats.h>
#include <bcmutils.h>
#include <dhd.h>
#include <dhd_dbg.h>
#include <dhd_linux.h>
#include <bcmdevs.h>

#include <linux/fcntl.h>
#include <linux/fs.h>
#include <linux/list.h>

struct dhd_info;
extern int _dhd_set_mac_address(struct dhd_info *dhd,
	int ifidx, struct ether_addr *addr);

struct cntry_locales_custom {
	char iso_abbrev[WLC_CNTRY_BUF_SZ]; /* ISO 3166-1 country abbreviation */
	char custom_locale[WLC_CNTRY_BUF_SZ]; /* Custom firmware locale */
	int32 custom_locale_rev; /* Custom local revisin default -1 */
};

typedef struct ether_mac_entry {
	struct list_head list;
	uint8 mac[ETHER_ADDR_LEN];
} ether_mac_entry_t;

/* Locale table for sec */
const struct cntry_locales_custom translate_custom_table[] = {
#if defined(BCM4330_CHIP) || defined(BCM4334_CHIP) || defined(BCM43241_CHIP)
	/* 4330/4334/43241 */
	{"AR", "AR", 1},
	{"AT", "AT", 1},
	{"AU", "AU", 2},
	{"BE", "BE", 1},
	{"BG", "BG", 1},
	{"BN", "BN", 1},
	{"CA", "CA", 2},
	{"CH", "CH", 1},
	{"CY", "CY", 1},
	{"CZ", "CZ", 1},
	{"DE", "DE", 3},
	{"DK", "DK", 1},
	{"EE", "EE", 1},
	{"ES", "ES", 1},
	{"FI", "FI", 1},
	{"FR", "FR", 1},
	{"GB", "GB", 1},
	{"GR", "GR", 1},
	{"HR", "HR", 1},
	{"HU", "HU", 1},
	{"IE", "IE", 1},
	{"IS", "IS", 1},
	{"IT", "IT", 1},
	{"JP", "JP", 5},
	{"KR", "KR", 24},
	{"KW", "KW", 1},
	{"LI", "LI", 1},
	{"LT", "LT", 1},
	{"LU", "LU", 1},
	{"LV", "LV", 1},
	{"MT", "MT", 1},
	{"NL", "NL", 1},
	{"NO", "NO", 1},
	{"PL", "PL", 1},
	{"PT", "PT", 1},
	{"PY", "PY", 1},
	{"RO", "RO", 1},
	{"RU", "RU", 13},
	{"SE", "SE", 1},
	{"SI", "SI", 1},
	{"SK", "SK", 1},
	{"TW", "TW", 2},
#ifdef BCM4330_CHIP
	{"",   "XZ", 1},	/* Universal if Country code is unknown or empty */
	{"IR", "XZ", 1},	/* Universal if Country code is IRAN, (ISLAMIC REPUBLIC OF) */
	{"SD", "XZ", 1},	/* Universal if Country code is SUDAN */
	{"SY", "XZ", 1},	/* Universal if Country code is SYRIAN ARAB REPUBLIC */
	{"GL", "XZ", 1},	/* Universal if Country code is GREENLAND */
	{"PS", "XZ", 1},	/* Universal if Country code is PALESTINIAN TERRITORY, OCCUPIED */
	{"TL", "XZ", 1},	/* Universal if Country code is TIMOR-LESTE (EAST TIMOR) */
	{"MH", "XZ", 1},	/* Universal if Country code is MARSHALL ISLANDS */
	{"JO", "XZ", 1},	/* Universal if Country code is Jordan */
	{"PG", "XZ", 1},	/* Universal if Country code is Papua New Guinea */
	{"SA", "XZ", 1},	/* Universal if Country code is Saudi Arabia */
	{"AF", "XZ", 1},	/* Universal if Country code is Afghanistan */
	{"US", "US", 5},
	{"UA", "UY", 0},
	{"AD", "AL", 0},
	{"CX", "AU", 2},
	{"GE", "GB", 1},
	{"ID", "MW", 0},
	{"KI", "AU", 2},
	{"NP", "SA", 0},
	{"WS", "SA", 0},
	{"LR", "BR", 0},
	{"ZM", "IN", 0},
	{"AN", "AG", 0},
	{"AI", "AS", 0},
	{"BM", "AS", 0},
	{"DZ", "GB", 1},
	{"LC", "AG", 0},
	{"MF", "BY", 0},
	{"GY", "CU", 0},
	{"LA", "GB", 1},
	{"LB", "BR", 0},
	{"MA", "IL", 0},
	{"MO", "BD", 0},
	{"MW", "BD", 0},
	{"QA", "BD", 0},
	{"TR", "GB", 1},
	{"TZ", "BF", 0},
	{"VN", "BR", 0},
	{"AE", "AZ", 0},
	{"IQ", "GB", 1},
	{"CN", "CL", 0},
	{"MX", "MX", 1},
#else
	/* 4334/43241 */
	{"",   "XZ", 11},	/* Universal if Country code is unknown or empty */
	{"IR", "XZ", 11},	/* Universal if Country code is IRAN, (ISLAMIC REPUBLIC OF) */
	{"SD", "XZ", 11},	/* Universal if Country code is SUDAN */
	{"SY", "XZ", 11},	/* Universal if Country code is SYRIAN ARAB REPUBLIC */
	{"GL", "XZ", 11},	/* Universal if Country code is GREENLAND */
	{"PS", "XZ", 11},	/* Universal if Country code is PALESTINIAN TERRITORY, OCCUPIED */
	{"TL", "XZ", 11},	/* Universal if Country code is TIMOR-LESTE (EAST TIMOR) */
	{"MH", "XZ", 11},	/* Universal if Country code is MARSHALL ISLANDS */
	{"US", "US", 46},
	{"UA", "UA", 8},
	{"CO", "CO", 4},
	{"ID", "ID", 1},
	{"LA", "LA", 1},
	{"LB", "LB", 2},
	{"VN", "VN", 4},
	{"MA", "MA", 1},
	{"TR", "TR", 7},
#endif /* defined(BCM4330_CHIP) */
#ifdef BCM4334_CHIP
	{"AE", "AE", 1},
	{"MX", "MX", 1},
#endif /* defined(BCM4334_CHIP) */
#ifdef BCM43241_CHIP
	{"AE", "AE", 6},
	{"BD", "BD", 2},
	{"CN", "CN", 38},
	{"MX", "MX", 20},
#endif /* defined(BCM43241_CHIP) */
#else  /* defined(BCM4330_CHIP) || defined(BCM4334_CHIP) || defined(BCM43241_CHIP) */
	/* default ccode/regrev */
	{"",   "XZ", 11},	/* Universal if Country code is unknown or empty */
	{"IR", "XZ", 11},	/* Universal if Country code is IRAN, (ISLAMIC REPUBLIC OF) */
	{"SD", "XZ", 11},	/* Universal if Country code is SUDAN */
	{"SY", "XZ", 11},	/* Universal if Country code is SYRIAN ARAB REPUBLIC */
	{"PS", "XZ", 11},	/* Universal if Country code is PALESTINIAN TERRITORY, OCCUPIED */
	{"TL", "XZ", 11},	/* Universal if Country code is TIMOR-LESTE (EAST TIMOR) */
	{"MH", "XZ", 11},	/* Universal if Country code is MARSHALL ISLANDS */
	{"GL", "GP", 2},
	{"AL", "AL", 2},
#ifdef DHD_SUPPORT_GB_999
	{"DZ", "GB", 999},
#else
	{"DZ", "GB", 6},
#endif /* DHD_SUPPORT_GB_999 */
	{"AS", "AS", 12},
	{"AI", "AI", 1},
	{"AF", "AD", 0},
	{"AG", "AG", 2},
	{"AR", "AU", 6},
	{"AW", "AW", 2},
	{"AU", "AU", 6},
	{"AT", "AT", 4},
	{"AZ", "AZ", 2},
	{"BS", "BS", 2},
	{"BH", "BH", 4},
	{"BD", "BD", 1},
	{"BY", "BY", 3},
	{"BE", "BE", 4},
	{"BM", "BM", 12},
	{"BA", "BA", 2},
	{"BR", "BR", 2},
	{"VG", "VG", 2},
	{"BN", "BN", 4},
	{"BG", "BG", 4},
	{"KH", "KH", 2},
	{"KY", "KY", 3},
	{"CN", "CN", 38},
	{"CO", "CO", 17},
	{"CR", "CR", 17},
	{"HR", "HR", 4},
	{"CY", "CY", 4},
	{"CZ", "CZ", 4},
	{"DK", "DK", 4},
	{"EE", "EE", 4},
	{"ET", "ET", 2},
	{"FI", "FI", 4},
	{"FR", "FR", 5},
	{"GF", "GF", 2},
	{"DE", "DE", 7},
	{"GR", "GR", 4},
	{"GD", "GD", 2},
	{"GP", "GP", 2},
	{"GU", "GU", 30},
	{"HK", "HK", 2},
	{"HU", "HU", 4},
	{"IS", "IS", 4},
	{"IN", "IN", 3},
	{"ID", "ID", 1},
	{"IE", "IE", 5},
	{"IL", "IL", 14},
	{"IT", "IT", 4},
	{"JO", "JO", 3},
	{"KE", "SA", 0},
	{"KW", "KW", 5},
	{"LA", "LA", 2},
	{"LV", "LV", 4},
	{"LB", "LB", 5},
	{"LS", "LS", 2},
	{"LI", "LI", 4},
	{"LT", "LT", 4},
	{"LU", "LU", 3},
	{"MO", "SG", 0},
	{"MK", "MK", 2},
	{"MW", "MW", 1},
	{"MY", "MY", 3},
	{"MV", "MV", 3},
	{"MT", "MT", 4},
	{"MQ", "MQ", 2},
	{"MR", "MR", 2},
	{"MU", "MU", 2},
	{"YT", "YT", 2},
	{"MX", "MX", 44},
	{"MD", "MD", 2},
	{"MC", "MC", 1},
	{"ME", "ME", 2},
	{"MA", "MA", 2},
	{"NL", "NL", 4},
	{"AN", "GD", 2},
	{"NZ", "NZ", 4},
	{"NO", "NO", 4},
	{"OM", "OM", 4},
	{"PA", "PA", 17},
	{"PG", "AU", 6},
	{"PY", "PY", 2},
	{"PE", "PE", 20},
	{"PH", "PH", 5},
	{"PL", "PL", 4},
	{"PT", "PT", 4},
	{"PR", "PR", 38},
	{"RE", "RE", 2},
	{"RO", "RO", 4},
	{"SN", "MA", 2},
	{"RS", "RS", 2},
	{"SK", "SK", 4},
	{"SI", "SI", 4},
	{"ES", "ES", 4},
	{"LK", "LK", 1},
	{"SE", "SE", 4},
	{"CH", "CH", 4},
	{"TW", "TW", 1},
	{"TH", "TH", 5},
	{"TT", "TT", 3},
	{"TR", "TR", 7},
	{"AE", "AE", 6},
#ifdef DHD_SUPPORT_GB_999
	{"GB", "GB", 999},
#else
	{"GB", "GB", 6},
#endif /* DHD_SUPPORT_GB_999 */
	{"UY", "VE", 3},
	{"VI", "PR", 38},
	{"VA", "VA", 2},
	{"VE", "VE", 3},
	{"VN", "VN", 4},
	{"ZM", "LA", 2},
	{"EC", "EC", 21},
	{"SV", "SV", 25},
#if defined(BCM4358_CHIP) || defined(BCM4359_CHIP)
	{"KR", "KR", 70},
#else
	{"KR", "KR", 48},
#endif
	{"JP", "JP", 968},
#ifdef DHD_SUPPORT_JP968_RU986_UA16
	{"RU", "RU", 986},
	{"UA", "UA", 16},
#else
	{"JP", "JP", 45},
	{"RU", "RU", 13},
	{"UA", "UA", 8},
#endif /* DHD_SUPPORT_JP968_RU986_UA16 */
	{"GT", "GT", 1},
	{"MN", "MN", 1},
	{"NI", "NI", 2},
	{"UZ", "MA", 2},
	{"ZA", "ZA", 6},
	{"EG", "EG", 13},
	{"TN", "TN", 1},
	{"AO", "AD", 0},
	{"BT", "BJ", 0},
	{"BW", "BJ", 0},
	{"LY", "LI", 4},
	{"BO", "NG", 0},
	{"UM", "PR", 38},
	/* Support FCC 15.407 (Part 15E) Changes, effective June 2 2014 */
	/* US/988, Q2/993 country codes with higher power on UNII-1 5G band */
#if defined(DHD_SUPPORT_US_949)
	{"US", "US", 949},
#elif defined(DHD_SUPPORT_US_945)
	{"US", "US", 945},
#else
	{"US", "US", 988},
#endif
	{"CU", "US", 988},
	{"CA", "Q2", 993},
#endif /* default ccode/regrev */
};

/* Customized Locale convertor
*  input : ISO 3166-1 country abbreviation
*  output: customized cspec
*/
void get_customized_country_code(void *adapter, char *country_iso_code, wl_country_t *cspec)
{
	int size, i;

	size = ARRAYSIZE(translate_custom_table);

	if (cspec == 0)
		 return;

	if (size == 0)
		 return;

	for (i = 0; i < size; i++) {
		if (strcmp(country_iso_code, translate_custom_table[i].iso_abbrev) == 0) {
			memcpy(cspec->ccode,
				translate_custom_table[i].custom_locale, WLC_CNTRY_BUF_SZ);
			cspec->rev = translate_custom_table[i].custom_locale_rev;
			return;
		}
	}
	return;
}

#ifdef PLATFORM_SLP
#define CIDINFO "/opt/etc/.cid.info"
#define PSMINFO "/opt/etc/.psm.info"
#define MACINFO "/opt/etc/.mac.info"
#define MACINFO_EFS NULL
#define REVINFO "/opt/etc/.rev"
#define WIFIVERINFO "/opt/etc/.wifiver.info"
#define ANTINFO "/opt/etc/.ant.info"
#define RSDBINFO "/opt/etc/.rsdb.info"
#define LOGTRACEINFO "/opt/etc/.logtrace.info"
#define WRMAC_BUF_SIZE 19
#else
#define MACINFO "/data/.mac.info"
#define MACINFO_EFS "/efs/wifi/.mac.info"
#define NVMACINFO "/data/.nvmac.info"
#define	REVINFO "/data/.rev"
#define CIDINFO "/data/.cid.info"
#define PSMINFO "/data/.psm.info"
#define WIFIVERINFO "/data/.wifiver.info"
#define ANTINFO "/data/.ant.info"
#define RSDBINFO "/data/.rsdb.info"
#define LOGTRACEINFO "/data/.logtrace.info"
#define WRMAC_BUF_SIZE 18
#endif /* PLATFORM_SLP */

#ifdef BCM4330_CHIP
#define CIS_BUF_SIZE            128
#elif defined(BCM4334_CHIP)
#define CIS_BUF_SIZE            256
#elif defined(BCM4359_CHIP)
#define CIS_BUF_SIZE            1024
#else
#define CIS_BUF_SIZE            512
#endif /* BCM4330_CHIP */

#define CIS_TUPLE_TAG_START		0x80
#define CIS_TUPLE_TAG_VENDOR		0x81
#define CIS_TUPLE_TAG_MACADDR		0x19
#define CIS_TUPLE_TAG_MACADDR_OFF	((TLV_BODY_OFF) + (1))
#define CIS_TUPLE_TAG_BOARDTYPE	0x1b
#define CIS_DUMP_END                    0xff
#define CIS_TUPLE_NULL                  0X00

#ifdef CONFIG_BCMDHD_PCIE
#define OTP_OFFSET 128
#else /* CONFIG_BCMDHD_PCIE */
#define OTP_OFFSET 12 /* SDIO */
#endif /* CONFIG_BCMDHD_PCIE */

#ifdef READ_MACADDR
int dhd_read_macaddr(struct dhd_info *dhd, struct ether_addr *mac)
{
	struct file *fp      = NULL;
	char macbuffer[18]   = {0};
	mm_segment_t oldfs   = {0};
	char randommac[3]    = {0};
	char buf[18]         = {0};
	char *filepath_efs       = MACINFO_EFS;
	int ret = 0;

	fp = filp_open(filepath_efs, O_RDONLY, 0);
	if (IS_ERR(fp)) {
start_readmac:
		/* File Doesn't Exist. Create and write mac addr. */
		fp = filp_open(filepath_efs, O_RDWR | O_CREAT, 0666);
		if (IS_ERR(fp)) {
			DHD_ERROR(("[WIFI_SEC] %s: File open error\n", filepath_efs));
			return -1;
		}
		oldfs = get_fs();
		set_fs(get_ds());

		/* Generating the Random Bytes for 3 last octects of the MAC address */
		get_random_bytes(randommac, 3);

		sprintf(macbuffer, "%02X:%02X:%02X:%02X:%02X:%02X\n",
			0x00, 0x12, 0x34, randommac[0], randommac[1], randommac[2]);
		DHD_ERROR(("[WIFI_SEC] The Random Generated MAC ID: %s\n", macbuffer));

		if (fp->f_mode & FMODE_WRITE) {
			ret = fp->f_op->write(fp, (const char *)macbuffer,
			sizeof(macbuffer), &fp->f_pos);
			if (ret < 0)
				DHD_ERROR(("[WIFI_SEC] MAC address [%s] Failed to write into File:"
					" %s\n", macbuffer, filepath_efs));
			else
				DHD_ERROR(("[WIFI_SEC] MAC address [%s] written into File: %s\n",
					macbuffer, filepath_efs));
		}
		set_fs(oldfs);
		/* Reading the MAC Address from .mac.info file
		   ( the existed file or just created file)
		 */
		ret = kernel_read(fp, 0, buf, 18);
	} else {
		/* Reading the MAC Address from
		   .mac.info file( the existed file or just created file)
		 */
		ret = kernel_read(fp, 0, buf, 18);
		/* to prevent abnormal string display
		* when mac address is displayed on the screen.
		*/
		buf[17] = '\0';
		if (strncmp(buf, "00:00:00:00:00:00", 17) < 1) {
			DHD_ERROR(("[WIFI_SEC] goto start_readmac \r\n"));
			filp_close(fp, NULL);
			goto start_readmac;
		}
	}

	if (ret)
		sscanf(buf, "%02X:%02X:%02X:%02X:%02X:%02X",
			(unsigned int *)&(mac->octet[0]), (unsigned int *)&(mac->octet[1]),
			(unsigned int *)&(mac->octet[2]), (unsigned int *)&(mac->octet[3]),
			(unsigned int *)&(mac->octet[4]), (unsigned int *)&(mac->octet[5]));
	else
		DHD_ERROR(("[WIFI_SEC] dhd_bus_start: Reading from the '%s' returns 0 bytes\n",
			filepath_efs));

	if (fp)
		filp_close(fp, NULL);

	/* Writing Newly generated MAC ID to the Dongle */
	if (_dhd_set_mac_address(dhd, 0, mac) == 0)
		DHD_INFO(("[WIFI_SEC] dhd_bus_start: MACID is overwritten\n"));
	else
		DHD_ERROR(("[WIFI_SEC] dhd_bus_start: _dhd_set_mac_address() failed\n"));

	return 0;
}
#endif /* READ_MACADDR */

#ifdef USE_CID_CHECK
static int dhd_write_cid_file(const char *filepath_cid, const char *buf, int buf_len)
{
	struct file *fp = NULL;
	mm_segment_t oldfs = {0};
	int ret = 0;

	/* File is always created. */
	fp = filp_open(filepath_cid, O_RDWR | O_CREAT, 0666);
	if (IS_ERR(fp)) {
		DHD_ERROR(("[WIFI_SEC] %s: File open error\n", filepath_cid));
		return -1;
	} else {
		oldfs = get_fs();
		set_fs(get_ds());

		if (fp->f_mode & FMODE_WRITE) {
			ret = fp->f_op->write(fp, buf, buf_len, &fp->f_pos);
			if (ret < 0)
				DHD_ERROR(("[WIFI_SEC] Failed to write CIS[%s]"
					" into '%s'\n", buf, filepath_cid));
			else
				DHD_ERROR(("[WIFI_SEC] CID [%s] written into"
					" '%s'\n", buf, filepath_cid));
		}
		set_fs(oldfs);
	}
	filp_close(fp, NULL);

	return 0;
}

#ifdef DUMP_CIS
static void dhd_dump_cis(const unsigned char *buf, int size)
{
	int i;
	for (i = 0; i < size; i++) {
		DHD_ERROR(("%02X ", buf[i]));
		if ((i % 15) == 15) DHD_ERROR(("\n"));
	}
	DHD_ERROR(("\n"));
}
#endif /* DUMP_CIS */

#define MAX_VID_LEN		8
#define MAX_VNAME_LEN		16

#ifdef	SUPPORT_MULTIPLE_BOARDTYPE
#define MAX_BNAME_LEN		6

typedef struct {
	uint8 b_len;
	unsigned char btype[MAX_VID_LEN];
	char bname[MAX_BNAME_LEN];
} board_info_t;

board_info_t semco_board_info[] = {
	{ 3, { 0x51, 0x07, }, { "_b90b" } },     /* semco three antenna */
	{ 3, { 0x61, 0x07, }, { "_b90b" } },     /* semco two antenna */
	{ 0, { 0x00, }, { "" } }   /* Default: Not specified yet */
};
board_info_t murata_board_info[] = {
	{ 3, { 0xa5, 0x07, }, { "_b90" } },      /* murata three antenna */
	{ 3, { 0xb0, 0x07, }, { "_b90b" } },     /* murata two antenna */
	{ 3, { 0xb1, 0x07, }, { "_es5" } },     /* murata two antenna */
	{ 0, { 0x00, }, { "" } }   /* Default: Not specified yet */
};
#else
#define MAX_BNAME_LEN		0
#endif /* SUPPORT_MULTIPLE_BOARDTYPE */

typedef struct {
	uint8 vid_length;
	unsigned char vid[MAX_VID_LEN];
	char vname[MAX_VNAME_LEN];
} vid_info_t;

#if defined(BCM4330_CHIP)
vid_info_t vid_info[] = {
	{ 6, { 0x00, 0x20, 0xc7, 0x00, 0x00, }, { "murata" } },
	{ 2, { 0x99, }, { "semcove" } },
	{ 0, { 0x00, }, { "samsung" } }
};
#elif defined(BCM4334_CHIP)
vid_info_t vid_info[] = {
	{ 6, { 0x00, 0x00, 0x00, 0x33, 0x33, }, { "semco" } },
	{ 6, { 0x00, 0x00, 0x00, 0xfb, 0x50, }, { "semcosh" } },
	{ 6, { 0x00, 0x20, 0xc7, 0x00, 0x00, }, { "murata" } },
	{ 0, { 0x00, }, { "murata" } }
};
#elif defined(BCM4335_CHIP)
vid_info_t vid_info[] = {
	{ 3, { 0x33, 0x66, }, { "semcosh" } },		/* B0 Sharp 5G-FEM */
	{ 3, { 0x33, 0x33, }, { "semco" } },		/* B0 Skyworks 5G-FEM and A0 chip */
	{ 3, { 0x33, 0x88, }, { "semco3rd" } },		/* B0 Syri 5G-FEM */
	{ 3, { 0x00, 0x11, }, { "muratafem1" } },	/* B0 ANADIGICS 5G-FEM */
	{ 3, { 0x00, 0x22, }, { "muratafem2" } },	/* B0 TriQuint 5G-FEM */
	{ 3, { 0x00, 0x33, }, { "muratafem3" } },	/* 3rd FEM: Reserved */
	{ 0, { 0x00, }, { "murata" } }	/* Default: for Murata A0 module */
};
#elif defined(BCM4339_CHIP) || defined(BCM4354_CHIP) || \
	defined(BCM4356_CHIP)
vid_info_t vid_info[] = {			  /* 4339:2G FEM+5G FEM ,4354: 2G FEM+5G FEM */
	{ 3, { 0x33, 0x33, }, { "semco" } },      /* 4339:Skyworks+sharp,4354:Panasonic+Panasonic */
	{ 3, { 0x33, 0x66, }, { "semco" } },      /* 4339:  , 4354:Panasonic+SEMCO */
	{ 3, { 0x33, 0x88, }, { "semco3rd" } },   /* 4339:  , 4354:SEMCO+SEMCO */
	{ 3, { 0x90, 0x01, }, { "wisol" } },      /* 4339:  , 4354:Microsemi+Panasonic */
	{ 3, { 0x90, 0x02, }, { "wisolfem1" } },  /* 4339:  , 4354:Panasonic+Panasonic */
	{ 3, { 0x90, 0x03, }, { "wisolfem2" } },  /* 4354:Murata+Panasonic */
	{ 3, { 0x00, 0x11, }, { "muratafem1" } }, /* 4339:  , 4354:Murata+Anadigics */
	{ 3, { 0x00, 0x22, }, { "muratafem2"} },  /* 4339:  , 4354:Murata+Triquint */
	{ 0, { 0x00, }, { "samsung" } }           /* Default: Not specified yet */
};
#elif defined(BCM4358_CHIP)
vid_info_t vid_info[] = {
	{ 3, { 0x33, 0x33, }, { "semco_b85" } },
	{ 3, { 0x33, 0x66, }, { "semco_b85" } },
	{ 3, { 0x33, 0x88, }, { "semco3rd_b85" } },
	{ 3, { 0x90, 0x01, }, { "wisol_b85" } },
	{ 3, { 0x90, 0x02, }, { "wisolfem1_b85" } },
	{ 3, { 0x90, 0x03, }, { "wisolfem2_b85" } },
	{ 3, { 0x31, 0x90, }, { "wisol_b85b" } },
	{ 3, { 0x00, 0x11, }, { "murata_b85" } },
	{ 3, { 0x00, 0x22, }, { "murata_b85"} },
	{ 6, { 0x00, 0xFF, 0xFF, 0x00, 0x00, }, { "murata_b85"} },
	{ 3, { 0x10, 0x33, }, { "semco_b85a" } },
	{ 3, { 0x30, 0x33, }, { "semco_b85b" } },
	{ 3, { 0x31, 0x33, }, { "semco_b85b" } },
	{ 3, { 0x10, 0x22, }, { "murata_b85a" } },
	{ 3, { 0x20, 0x22, }, { "murata_b85a" } },
	{ 3, { 0x21, 0x22, }, { "murata_b85a" } },
	{ 3, { 0x23, 0x22, }, { "murata_b85a" } },
	{ 3, { 0x31, 0x22, }, { "murata_b85b" } },
	{ 0, { 0x00, }, { "samsung" } }           /* Default: Not specified yet */
};
#elif defined(BCM4359_CHIP)
vid_info_t vid_info[] = {
#if defined(SUPPORT_BCM4359_MIXED_MODULES)
	{ 3, { 0x34, 0x33, }, { "semco_b90b" } },
	{ 3, { 0x40, 0x33, }, { "semco_b90b" } },
	{ 3, { 0x41, 0x33, }, { "semco_b90b" } },
	{ 3, { 0x11, 0x33, }, { "semco_b90b" } },
	{ 3, { 0x33, 0x66, }, { "semco_b90b" } },
	{ 3, { 0x23, 0x22, }, { "murata_b90b" } },
	{ 3, { 0x40, 0x22, }, { "murata_b90b" } },
	{ 3, { 0x10, 0x90, }, { "wisol_b90b" } },
	{ 3, { 0x33, 0x33, }, { "semco_b90s_b1" } },
	{ 3, { 0x66, 0x33, }, { "semco_b90s_c0" } },
	{ 3, { 0x60, 0x22, }, { "murata_b90s_b1" } },
	{ 3, { 0x61, 0x22, }, { "murata_b90s_b1" } },
	{ 3, { 0x62, 0x22, }, { "murata_b90s_b1" } },
	{ 3, { 0x63, 0x22, }, { "murata_b90s_b1" } },
	{ 3, { 0x70, 0x22, }, { "murata_b90s_c0" } },
	{ 3, { 0x71, 0x22, }, { "murata_b90s_c0" } },
	{ 3, { 0x72, 0x22, }, { "murata_b90s_c0" } },
	{ 3, { 0x73, 0x22, }, { "murata_b90s_c0" } },
	{ 0, { 0x00, }, { "samsung" } }           /* Default: Not specified yet */
#else /* SUPPORT_BCM4359_MIXED_MODULES */
	{ 3, { 0x34, 0x33, }, { "semco" } },
	{ 3, { 0x40, 0x33, }, { "semco" } },
	{ 3, { 0x41, 0x33, }, { "semco" } },
	{ 3, { 0x11, 0x33, }, { "semco" } },
	{ 3, { 0x33, 0x66, }, { "semco" } },
	{ 3, { 0x23, 0x22, }, { "murata" } },
	{ 3, { 0x40, 0x22, }, { "murata" } },
	{ 3, { 0x51, 0x22, }, { "murata" } },
	{ 3, { 0x52, 0x22, }, { "murata" } },
	{ 3, { 0x10, 0x90, }, { "wisol" } },
	{ 0, { 0x00, }, { "samsung" } }           /* Default: Not specified yet */
#endif /* SUPPORT_BCM4359_MIXED_MODULES */
};
#else
vid_info_t vid_info[] = {
	{ 0, { 0x00, }, { "samsung" } }			/* Default: Not specified yet */
};
#endif /* BCM_CHIP_ID */

int find_tuple_from_otp(unsigned char* cis_buf, int buffsize, int req_tup,
	unsigned char* req_tup_len)
{
	int idx = OTP_OFFSET;
	int tup, tup_len = 0;

	do {
		tup = cis_buf[idx++];
		if (tup == CIS_TUPLE_NULL || tup == CIS_DUMP_END) {
			tup_len = 0;
		} else {
			tup_len = cis_buf[idx++];
			if (idx + tup_len > buffsize) {
				return -1;
			}

			if (tup == CIS_TUPLE_TAG_START && tup_len != CIS_TUPLE_NULL &&
				cis_buf[idx] == req_tup) {
				*req_tup_len = tup_len;
				idx++;
				return idx;
			}
		}
		idx += tup_len;
	} while (tup != CIS_DUMP_END && idx < buffsize);

	return -1;
}

int dhd_check_module_cid(dhd_pub_t *dhd)
{
	int ret = -1;
	unsigned char cis_buf[CIS_BUF_SIZE] = {0};
	const char *cidfilepath = CIDINFO;
	cis_rw_t *cish = (cis_rw_t *)&cis_buf[8];
	int idx, max;
	vid_info_t *cur_info;
	unsigned char *vid_start = NULL;
	unsigned char vid_length = 0;
#ifdef SUPPORT_MULTIPLE_BOARDTYPE
	board_info_t *cur_b_info = NULL;
	board_info_t *vendor_b_info = NULL;
	unsigned char *btype_start;
	unsigned char boardtype_len = 0;
#endif /* SUPPORT_MULTIPLE_BOARDTYPE */
	unsigned char cid_info[MAX_VNAME_LEN + MAX_BNAME_LEN];
	bool found = FALSE;
#if defined(BCM4334_CHIP) || defined(BCM4335_CHIP)
	const char *revfilepath = REVINFO;
#ifdef BCM4334_CHIP
	int flag_b3;
#else
	char rev_str[10] = {0};
#endif /* BCM4334_CHIP */
#endif /* BCM4334_CHIP || BCM4335_CHIP */

	/* Try reading out from CIS */
	cish->source = 0;
	cish->byteoff = 0;
	cish->nbytes = sizeof(cis_buf);

	strcpy(cis_buf, "cisdump");
	ret = dhd_wl_ioctl_cmd(dhd, WLC_GET_VAR, cis_buf,
		sizeof(cis_buf), 0, 0);
	if (ret < 0) {
		DHD_INFO(("[WIFI_SEC] %s: CIS reading failed, ret=%d\n",
			__FUNCTION__, ret));
		return ret;
	}

	DHD_ERROR(("[WIFI_SEC] %s: CIS reading success, ret=%d\n",
		__FUNCTION__, ret));
#ifdef DUMP_CIS
	dhd_dump_cis(cis_buf, 48);
#endif
	max = sizeof(cis_buf);
	idx = find_tuple_from_otp(cis_buf, max, CIS_TUPLE_TAG_VENDOR, &vid_length);
	if (idx > 0) {
		found = TRUE;
		vid_start = &cis_buf[idx];
	}

	if (found) {
		max = sizeof(vid_info) / sizeof(vid_info_t);
		for (idx = 0; idx < max; idx++) {
			cur_info = &vid_info[idx];
#if defined(BCM4358_CHIP)
			if (cur_info->vid_length  == 6 && vid_length == 6) {
				if (cur_info->vid[0] == vid_start[0] &&
				    cur_info->vid[3] == vid_start[3] &&
				    cur_info->vid[4] == vid_start[4])
				goto check_board_type;
			}
#endif /* BCM4358_CHIP */
			if ((cur_info->vid_length == vid_length) &&
				(cur_info->vid_length != 0) &&
				(memcmp(cur_info->vid, vid_start, cur_info->vid_length - 1) == 0))
				goto check_board_type;
		}
	}

	/* find default nvram, if exist */
	DHD_ERROR(("[WIFI_SEC] %s: cannot find CIS TUPLE set as default\n", __FUNCTION__));
	max = sizeof(vid_info) / sizeof(vid_info_t);
	for (idx = 0; idx < max; idx++) {
		cur_info = &vid_info[idx];
		if (cur_info->vid_length == 0)
			goto write_cid;
	}
	DHD_ERROR(("[WIFI_SEC] %s: cannot find default CID\n", __FUNCTION__));
	return -1;

check_board_type:
#ifdef SUPPORT_MULTIPLE_BOARDTYPE
	max = sizeof(cis_buf) - 4;
	for (idx = 0; idx < max; idx++) {
		if (cis_buf[idx] == CIS_TUPLE_TAG_START &&
			cis_buf[idx + 2] == CIS_TUPLE_TAG_BOARDTYPE) {
			boardtype_len = cis_buf[idx + 1];
			btype_start = &cis_buf[idx + 3];

			/* Check buffer overflow */
			if (&cis_buf[idx + 1] + boardtype_len
				<= &cis_buf[CIS_BUF_SIZE - 1]) {
				DHD_INFO(("[WIFI_SEC] %s: board type found.\n",
					__FUNCTION__));
				break;
			} else {
				boardtype_len = 0;
			}
		}
	}

	if (strcmp(cur_info->vname, "semco") == 0) {
		vendor_b_info = semco_board_info;
		max = sizeof(semco_board_info) / sizeof(board_info_t);
	} else if (strcmp(cur_info->vname, "murata") == 0) {
		vendor_b_info = murata_board_info;
		max = sizeof(murata_board_info) / sizeof(board_info_t);
	} else {
		max = 0;
	}

	if (boardtype_len) {
		for (idx = 0; idx < max; idx++) {
			cur_b_info = vendor_b_info;
			if ((cur_b_info->b_len == boardtype_len) &&
					(cur_b_info->b_len != 0) &&
					(memcmp(cur_b_info->btype, btype_start,
					cur_b_info->b_len - 1) == 0)) {
				DHD_INFO(("[WIFI_SEC] %s : board type name : %s\n",
					__FUNCTION__, cur_b_info->bname));
				break;
			}
			cur_b_info = NULL;
			vendor_b_info++;
		}
	}
#endif /* SUPPORT_MULTIPLE_BOARDTYPE */

write_cid:
#ifdef SUPPORT_MULTIPLE_BOARDTYPE
	if (cur_b_info && cur_b_info->b_len > 0) {
		strcpy(cid_info, cur_info->vname);
		strcpy(cid_info + strlen(cur_info->vname), cur_b_info->bname);
	} else
#endif /* SUPPORT_MULTIPLE_BOARDTYPE */
	strcpy(cid_info, cur_info->vname);

	DHD_ERROR(("[WIFI_SEC] CIS MATCH FOUND : %s\n", cid_info));
	dhd_write_cid_file(cidfilepath, cid_info, strlen(cid_info)+1);

#if defined(BCM4334_CHIP)
	/* Try reading out from OTP to distinguish B2 or B3 */
	memset(cis_buf, 0, sizeof(cis_buf));
	cish = (cis_rw_t *)&cis_buf[8];

	cish->source = 0;
	cish->byteoff = 0;
	cish->nbytes = sizeof(cis_buf);

	strcpy(cis_buf, "otpdump");
	ret = dhd_wl_ioctl_cmd(dhd, WLC_GET_VAR, cis_buf,
		sizeof(cis_buf), 0, 0);
	if (ret < 0) {
		DHD_ERROR(("[WIFI_SEC] %s: OTP reading failed, err=%d\n",
			__FUNCTION__, ret));
		return ret;
	}

	/* otp 33th character is identifier for 4334B3 */
	cis_buf[34] = '\0';
	flag_b3 = bcm_atoi(&cis_buf[33]);
	if (flag_b3 & 0x1) {
		DHD_ERROR(("[WIFI_SEC] REV MATCH FOUND : 4334B3, %c\n", cis_buf[33]));
		dhd_write_cid_file(revfilepath, "4334B3", 6);
	}
#endif /* BCM4334_CHIP */
#if defined(BCM4335_CHIP)
	DHD_TRACE(("[WIFI_SEC] %s: BCM4335 Multiple Revision Check\n", __FUNCTION__));
	if (concate_revision(dhd->bus, rev_str, rev_str) < 0) {
		DHD_ERROR(("[WIFI_SEC] %s: fail to concate revision\n", __FUNCTION__));
		ret = -1;
	} else {
		if (strstr(rev_str, "_a0")) {
			DHD_ERROR(("[WIFI_SEC] REV MATCH FOUND : 4335A0\n"));
			dhd_write_cid_file(revfilepath, "BCM4335A0", 9);
		} else {
			DHD_ERROR(("[WIFI_SEC] REV MATCH FOUND : 4335B0\n"));
			dhd_write_cid_file(revfilepath, "BCM4335B0", 9);
		}
	}
#endif /* BCM4335_CHIP */

	return ret;
}
#endif /* USE_CID_CHECK */

#ifdef GET_MAC_FROM_OTP
static int dhd_write_mac_file(const char *filepath, const char *buf, int buf_len)
{
	struct file *fp = NULL;
	mm_segment_t oldfs = {0};
	int ret = 0;

	fp = filp_open(filepath, O_RDWR | O_CREAT, 0666);
	/* File is always created. */
	if (IS_ERR(fp)) {
		DHD_ERROR(("[WIFI_SEC] File open error\n"));
		return -1;
	} else {
		oldfs = get_fs();
		set_fs(get_ds());

		if (fp->f_mode & FMODE_WRITE) {
			ret = fp->f_op->write(fp, buf, buf_len, &fp->f_pos);
			if (ret < 0)
				DHD_ERROR(("[WIFI_SEC] Failed to write CIS. \n"));
			else
				DHD_ERROR(("[WIFI_SEC] MAC written. \n"));
		}
		set_fs(oldfs);
	}
	filp_close(fp, NULL);

	return 0;
}

static
ether_mac_entry_t *dhd_alloc_ether_mac_entry(dhd_pub_t *dhd, const uint8 *mac)
{
	ether_mac_entry_t *entry;

	entry = MALLOC(dhd->osh, sizeof(ether_mac_entry_t));
	if (!entry) {
		DHD_ERROR(("%s: failed to alloc\n", __FUNCTION__));
		return NULL;
	}

	strncpy(entry->mac, mac, ETHER_ADDR_LEN);

	return entry;
}

static
void dhd_free_ether_mac_entry(dhd_pub_t *dhd, struct list_head *list)
{
	ether_mac_entry_t *entry;

	while (!list_empty(list)) {
		entry = list_entry(list->next, ether_mac_entry_t, list);
		list_del(&entry->list);

		MFREE(dhd->osh, entry, sizeof(ether_mac_entry_t));
	}
}

static
ether_mac_entry_t *dhd_verify_mac_addr(dhd_pub_t *dhd, struct list_head *head)
{
	ether_mac_entry_t *cur;
	ether_mac_entry_t *next;

	list_for_each_entry(cur, head, list) {
		list_for_each_entry(next, &cur->list, list) {
			if (!strncmp(cur->mac, next->mac, ETHER_ADDR_LEN)) {
				return cur;
			}

			if (next->list.next == head) {
				break;
			}
		}
	}

	return NULL;
}

int dhd_check_module_mac(dhd_pub_t *dhd, struct ether_addr *mac)
{
	int ret = -1;
	unsigned char cis_buf[CIS_BUF_SIZE] = {0};
	unsigned char mac_buf[20] = {0};
	unsigned char otp_mac_buf[20] = {0};
	const char *macfilepath = MACINFO_EFS;

	/* Try reading out from CIS */
	cis_rw_t *cish = (cis_rw_t *)&cis_buf[8];
	struct file *fp_mac = NULL;

	struct list_head list;
	ether_mac_entry_t *mac_entry;
	uint8 mac_entry_count = 0;

	INIT_LIST_HEAD(&list);

	cish->source = 0;
	cish->byteoff = 0;
	cish->nbytes = sizeof(cis_buf);

	strcpy(cis_buf, "cisdump");
	ret = dhd_wl_ioctl_cmd(dhd, WLC_GET_VAR, cis_buf,
		sizeof(cis_buf), 0, 0);
	if (ret < 0) {
		DHD_INFO(("[WIFI_SEC] %s: CIS reading failed, ret=%d\n",
			__FUNCTION__, ret));

		fp_mac = filp_open(macfilepath, O_RDONLY, 0);
		if (!IS_ERR(fp_mac)) {
			DHD_ERROR(("[WIFI_SEC] Get Mac address in .mac.info \n"));
			kernel_read(fp_mac, fp_mac->f_pos, mac_buf, sizeof(mac_buf));
			filp_close(fp_mac, NULL);

			sscanf(mac_buf, "%02X:%02X:%02X:%02X:%02X:%02X",
				(unsigned int *)&(mac->octet[0]), (unsigned int *)&(mac->octet[1]),
				(unsigned int *)&(mac->octet[2]), (unsigned int *)&(mac->octet[3]),
				(unsigned int *)&(mac->octet[4]), (unsigned int *)&(mac->octet[5]));

			ret = _dhd_set_mac_address(dhd->info, 0, mac);
			if (ret  == 0) {
				DHD_INFO(("[WIFI_SEC] %s: MACID is overwritten\n",__FUNCTION__));
			} else {
				DHD_ERROR(("[WIFI_SEC] %s: _dhd_set_mac_address() failed, error=%d\n", __FUNCTION__, ret));
			}
		} else {
			DHD_ERROR(("[WIFI_SEC] %s: Can't read .mac.info file error=%ld \n", __FUNCTION__, PTR_ERR(fp_mac)));
		}
		sprintf(otp_mac_buf, "%02X:%02X:%02X:%02X:%02X:%02X\n",
			mac->octet[0], mac->octet[1], mac->octet[2],
			mac->octet[3], mac->octet[4], mac->octet[5]);
		DHD_ERROR(("[WIFI_SEC] %s: Check module mac by legacy FW : " MACDBG "\n",
			__FUNCTION__, MAC2STRDBG(mac->octet)));
	} else {
		int max, idx, macaddr_idx;
#ifdef DUMP_CIS
		dhd_dump_cis(cis_buf, 48);
#endif

		/* Find a new tuple tag */
		max = sizeof(cis_buf) - 8;
		for (idx = 0; idx < max; idx++) {
			if (cis_buf[idx] == CIS_TUPLE_TAG_START) {
				if (cis_buf[idx + 2] == CIS_TUPLE_TAG_MACADDR &&
					cis_buf[idx + 1] == 7) {
					macaddr_idx = idx + 3;
					/* found MAC Address tuple */
					mac_entry = dhd_alloc_ether_mac_entry(dhd,
							&cis_buf[macaddr_idx]);
					if (mac_entry) {
						list_add_tail(&mac_entry->list, &list);
						mac_entry_count++;
					}
					idx += (ETHER_ADDR_LEN + 2);
				}
			}
		}

		if (!list_empty(&list)) {
			if (mac_entry_count == 1) {
				sprintf(otp_mac_buf, "%02X:%02X:%02X:%02X:%02X:%02X\n",
					cis_buf[macaddr_idx], cis_buf[macaddr_idx + 1],
					cis_buf[macaddr_idx + 2], cis_buf[macaddr_idx + 3],
					cis_buf[macaddr_idx + 4], cis_buf[macaddr_idx + 5]);

				memcpy(mac->octet, &cis_buf[macaddr_idx], ETHER_ADDR_LEN);
				DHD_ERROR(("[WIFI_SEC] MAC address is taken from OTP\n"));
			} else {
				mac_entry = dhd_verify_mac_addr(dhd, &list);
				if (mac_entry) {
					sprintf(otp_mac_buf, "%02X:%02X:%02X:%02X:%02X:%02X\n",
						mac_entry->mac[0], mac_entry->mac[1],
						mac_entry->mac[2], mac_entry->mac[3],
						mac_entry->mac[4], mac_entry->mac[5]);

					memcpy(mac->octet, mac_entry->mac, ETHER_ADDR_LEN);
					DHD_ERROR(("[WIFI_SEC] MAC address is taken from OTP\n"));
				} else {
					DHD_ERROR(("[WIFI_SEC] fail to verify OTP stored mac address\n"));
					goto default_mac;
				}
			}
		} else {
default_mac:
			sprintf(otp_mac_buf, "%02X:%02X:%02X:%02X:%02X:%02X\n",
				mac->octet[0], mac->octet[1], mac->octet[2],
				mac->octet[3], mac->octet[4], mac->octet[5]);
			DHD_ERROR(("[WIFI_SEC] %s: Cannot find MAC address info from OTP,"
				" Check module mac by initial value: " MACDBG "\n",
				__FUNCTION__, MAC2STRDBG(mac->octet)));
		}
		ret = _dhd_set_mac_address(dhd->info, 0, mac);
		if (ret == 0) {
			DHD_INFO(("[WIFI_SEC] %s: MACID is overwritten in MFG mode\n",__FUNCTION__));
		} else {
			DHD_ERROR(("[WIFI_SEC] %s: _dhd_set_mac_address() failed,"
				" error=%d in MFG mode\n", __FUNCTION__, ret));
		}
		dhd_free_ether_mac_entry(dhd, &list);
	}

	fp_mac = filp_open(macfilepath, O_RDONLY, 0);
	if (!IS_ERR(fp_mac)) {
		DHD_ERROR(("[WIFI_SEC] Check Mac address in .mac.info \n"));
		kernel_read(fp_mac, fp_mac->f_pos, mac_buf, sizeof(mac_buf));
		filp_close(fp_mac, NULL);

		if (strncmp(mac_buf, otp_mac_buf, 17) != 0) {
			DHD_ERROR(("[WIFI_SEC] file MAC is wrong. Write OTP MAC in .mac.info \n"));
			dhd_write_mac_file(macfilepath, otp_mac_buf, sizeof(otp_mac_buf));
		}
	} else {
		DHD_ERROR(("[WIFI_SEC] %s: Can't read .mac.info file error=%ld \n", __FUNCTION__, PTR_ERR(fp_mac)));
	}

	return ret;
}
#endif /* GET_MAC_FROM_OTP */

#ifdef WRITE_MACADDR
int dhd_write_macaddr(struct ether_addr *mac)
{
	char *filepath_data      = MACINFO;
	char *filepath_efs      = MACINFO_EFS;

	struct file *fp_mac = NULL;
	char buf[WRMAC_BUF_SIZE]      = {0};
	mm_segment_t oldfs    = {0};
	int ret = -1;
	int retry_count = 0;

startwrite:

	sprintf(buf, "%02X:%02X:%02X:%02X:%02X:%02X\n",
		mac->octet[0], mac->octet[1], mac->octet[2],
		mac->octet[3], mac->octet[4], mac->octet[5]);

	/* File will be created /data/.mac.info. */
	fp_mac = filp_open(filepath_data, O_RDWR | O_CREAT, 0666);

	if (IS_ERR(fp_mac)) {
		DHD_ERROR(("[WIFI_SEC] %s: File open error\n", filepath_data));
		return -1;
	} else {
		oldfs = get_fs();
		set_fs(get_ds());

		if (fp_mac->f_mode & FMODE_WRITE) {
			ret = fp_mac->f_op->write(fp_mac, (const char *)buf,
				sizeof(buf), &fp_mac->f_pos);
			if (ret < 0)
				DHD_ERROR(("[WIFI_SEC] Mac address [%s] Failed to"
				" write into File: %s\n", buf, filepath_data));
			else
				DHD_INFO(("[WIFI_SEC] Mac address [%s] written"
				" into File: %s\n", buf, filepath_data));
		}
		set_fs(oldfs);
		filp_close(fp_mac, NULL);
	}
	/* check .mac.info file is 0 byte */
	fp_mac = filp_open(filepath_data, O_RDONLY, 0);
	ret = kernel_read(fp_mac, 0, buf, 18);

	if ((ret == 0) && (retry_count++ < 3)) {
		filp_close(fp_mac, NULL);
		goto startwrite;
	}

	filp_close(fp_mac, NULL);
	/* end of /data/.mac.info */

	if (filepath_efs == NULL) {
		DHD_ERROR(("[WIFI_SEC] %s : no efs filepath", __func__));
		return 0;
	}

	/* File will be created /efs/wifi/.mac.info. */
	fp_mac = filp_open(filepath_efs, O_RDWR | O_CREAT, 0666);

	if (IS_ERR(fp_mac)) {
		DHD_ERROR(("[WIFI_SEC] %s: File open error\n", filepath_efs));
		return -1;
	} else {
		oldfs = get_fs();
		set_fs(get_ds());

		if (fp_mac->f_mode & FMODE_WRITE) {
			ret = fp_mac->f_op->write(fp_mac, (const char *)buf,
				sizeof(buf), &fp_mac->f_pos);
			if (ret < 0)
				DHD_ERROR(("[WIFI_SEC] Mac address [%s] Failed to"
				" write into File: %s\n", buf, filepath_efs));
			else
				DHD_INFO(("[WIFI_SEC] Mac address [%s] written"
				" into File: %s\n", buf, filepath_efs));
		}
		set_fs(oldfs);
		filp_close(fp_mac, NULL);
	}

	/* check .mac.info file is 0 byte */
	fp_mac = filp_open(filepath_efs, O_RDONLY, 0);
	ret = kernel_read(fp_mac, 0, buf, 18);

	if ((ret == 0) && (retry_count++ < 3)) {
		filp_close(fp_mac, NULL);
		goto startwrite;
	}

	filp_close(fp_mac, NULL);

	return 0;
}
#endif /* WRITE_MACADDR */

#ifdef DHD_PM_CONTROL_FROM_FILE
extern bool g_pm_control;
void sec_control_pm(dhd_pub_t *dhd, uint *power_mode)
{
	struct file *fp = NULL;
	char *filepath = PSMINFO;
	char power_val = 0;
	char iovbuf[WL_EVENTING_MASK_LEN + 12];
	int ret = 0;
#ifdef DHD_ENABLE_LPC
	uint32 lpc = 0;
#endif /* DHD_ENABLE_LPC */

	g_pm_control = FALSE;

	fp = filp_open(filepath, O_RDONLY, 0);
	if (IS_ERR(fp) || (fp == NULL)) {
		/* Enable PowerSave Mode */
		dhd_wl_ioctl_cmd(dhd, WLC_SET_PM, (char *)power_mode,
			sizeof(uint), TRUE, 0);
		DHD_ERROR(("[WIFI_SEC] %s: /data/.psm.info doesn't exist"
			" so set PM to %d\n",
			__FUNCTION__, *power_mode));
		return;
	} else {
		kernel_read(fp, fp->f_pos, &power_val, 1);
		DHD_ERROR(("[WIFI_SEC] %s: POWER_VAL = %c \r\n", __FUNCTION__, power_val));

		if (power_val == '0') {
#ifdef ROAM_ENABLE
			uint roamvar = 1;
#endif
			uint32 ocl_enable = 0;
			uint32 wl_updown = 1;

			*power_mode = PM_OFF;
			/* Disable PowerSave Mode */
			dhd_wl_ioctl_cmd(dhd, WLC_SET_PM, (char *)power_mode,
				sizeof(uint), TRUE, 0);
			/* Turn off MPC in AP mode */
			bcm_mkiovar("mpc", (char *)power_mode, 4,
				iovbuf, sizeof(iovbuf));
			dhd_wl_ioctl_cmd(dhd, WLC_SET_VAR, iovbuf,
				sizeof(iovbuf), TRUE, 0);
			g_pm_control = TRUE;
#ifdef ROAM_ENABLE
			/* Roaming off of dongle */
			bcm_mkiovar("roam_off", (char *)&roamvar, 4,
				iovbuf, sizeof(iovbuf));
			dhd_wl_ioctl_cmd(dhd, WLC_SET_VAR, iovbuf,
				sizeof(iovbuf), TRUE, 0);
#endif
#ifdef DHD_ENABLE_LPC
			/* Set lpc 0 */
			bcm_mkiovar("lpc", (char *)&lpc, 4, iovbuf, sizeof(iovbuf));
			if ((ret = dhd_wl_ioctl_cmd(dhd, WLC_SET_VAR, iovbuf,
				sizeof(iovbuf), TRUE, 0)) < 0) {
				DHD_ERROR(("[WIFI_SEC] %s: Set lpc failed  %d\n",
				__FUNCTION__, ret));
			}
#endif /* DHD_ENABLE_LPC */
#ifdef DHD_PCIE_RUNTIMEPM
			DHD_ERROR(("[WIFI_SEC] %s : Turn Runtime PM off \n", __FUNCTION__));
			/* Turn Runtime PM off */
			dhdpcie_block_runtime_pm(dhd);
#endif /* DHD_PCIE_RUNTIMEPM */
			/* Disable ocl */
			if ((ret = dhd_wl_ioctl_cmd(dhd, WLC_UP, (char *)&wl_updown,
					sizeof(wl_updown), TRUE, 0)) < 0) {
				DHD_ERROR(("[WIFI_SEC] %s: WLC_UP faield %d\n", __FUNCTION__, ret));
			}

			bcm_mkiovar("ocl_enable", (char *)&ocl_enable, 4, iovbuf, sizeof(iovbuf));
			if ((ret = dhd_wl_ioctl_cmd(dhd, WLC_SET_VAR, iovbuf,
					sizeof(iovbuf), TRUE, 0)) < 0) {
				DHD_ERROR(("[WIFI_SEC] %s: Set ocl_enable %d failed %d\n",
						__FUNCTION__, ocl_enable, ret));
			} else {
				DHD_ERROR(("[WIFI_SEC] %s: Set ocl_enable %d succeeded %d\n",
						__FUNCTION__, ocl_enable, ret));
			}

			if ((ret = dhd_wl_ioctl_cmd(dhd, WLC_DOWN, (char *)&wl_updown,
					sizeof(wl_updown), TRUE, 0)) < 0) {
				DHD_ERROR(("[WIFI_SEC] %s: WLC_DOWN faield %d\n",
						__FUNCTION__, ret));
			}
		} else {
			dhd_wl_ioctl_cmd(dhd, WLC_SET_PM, (char *)power_mode,
				sizeof(uint), TRUE, 0);
		}
	}

	if (fp)
		filp_close(fp, NULL);
}
#endif /* DHD_PM_CONTROL_FROM_FILE */

#ifdef MIMO_ANT_SETTING
int dhd_sel_ant_from_file(dhd_pub_t *dhd)
{
	struct file *fp = NULL;
	int ret = -1;
	uint32 ant_val = 0;
	uint32 btc_mode = 0;
	uint32 rsdb_mode = 0;
	char *filepath = ANTINFO;
	char iovbuf[WLC_IOCTL_SMLEN];
	uint chip_id = dhd_bus_chip_id(dhd);

	/* Check if this chip can support MIMO */
	if (chip_id != BCM4324_CHIP_ID &&
		chip_id != BCM4350_CHIP_ID &&
		chip_id != BCM4354_CHIP_ID &&
		chip_id != BCM4356_CHIP_ID &&
		chip_id != BCM43569_CHIP_ID &&
		chip_id != BCM4358_CHIP_ID &&
		chip_id != BCM4359_CHIP_ID &&
		chip_id != BCM4355_CHIP_ID) {
		DHD_ERROR(("[WIFI_SEC] %s: This chipset does not support MIMO\n",
			__FUNCTION__));
		return ret;
	}

	/* Read antenna settings from the file */
	fp = filp_open(filepath, O_RDONLY, 0);
	if (IS_ERR(fp)) {
		DHD_ERROR(("[WIFI_SEC] %s: File [%s] doesn't exist\n", __FUNCTION__, filepath));
		return ret;
	} else {
		ret = kernel_read(fp, 0, (char *)&ant_val, 4);
		if (ret < 0) {
			DHD_ERROR(("[WIFI_SEC] %s: File read error, ret=%d\n", __FUNCTION__, ret));
			filp_close(fp, NULL);
			return ret;
		}

		ant_val = bcm_atoi((char *)&ant_val);

		DHD_ERROR(("[WIFI_SEC]%s: ANT val = %d\n", __FUNCTION__, ant_val));
		filp_close(fp, NULL);

		/* Check value from the file */
		if (ant_val < 1 || ant_val > 3) {
			DHD_ERROR(("[WIFI_SEC] %s: Invalid value %d read from the file %s\n",
				__FUNCTION__, ant_val, filepath));
			return -1;
		}
	}

	/* bt coex mode off */
	if (dhd_get_fw_mode(dhd->info) == DHD_FLAG_MFG_MODE) {
		bcm_mkiovar("btc_mode", (char *)&btc_mode, 4, iovbuf, sizeof(iovbuf));
		ret = dhd_wl_ioctl_cmd(dhd, WLC_SET_VAR, iovbuf, sizeof(iovbuf), TRUE, 0);
		if (ret) {
			DHD_ERROR(("[WIFI_SEC] %s: Fail to execute dhd_wl_ioctl_cmd(): "
				"btc_mode, ret=%d\n",
				__FUNCTION__, ret));
			return ret;
		}
	}

	/* rsdb mode off */
	DHD_ERROR(("[WIFI_SEC] %s: %s the RSDB mode!\n",
		__FUNCTION__, rsdb_mode ? "Enable" : "Disable"));
	bcm_mkiovar("rsdb_mode", (char *)&rsdb_mode, 4, iovbuf, sizeof(iovbuf));
	ret = dhd_wl_ioctl_cmd(dhd, WLC_SET_VAR, iovbuf, sizeof(iovbuf), TRUE, 0);
	if (ret) {
		DHD_ERROR(("[WIFI_SEC] %s: Fail to execute dhd_wl_ioctl_cmd(): "
			"rsdb_mode, ret=%d\n", __FUNCTION__, ret));
		return ret;
	}

	/* Select Antenna */
	bcm_mkiovar("txchain", (char *)&ant_val, 4, iovbuf, sizeof(iovbuf));
	ret = dhd_wl_ioctl_cmd(dhd, WLC_SET_VAR, iovbuf, sizeof(iovbuf), TRUE, 0);
	if (ret) {
		DHD_ERROR(("[WIFI_SEC] %s: Fail to execute dhd_wl_ioctl_cmd(): txchain, ret=%d\n",
			__FUNCTION__, ret));
		return ret;
	}

	bcm_mkiovar("rxchain", (char *)&ant_val, 4, iovbuf, sizeof(iovbuf));
	ret = dhd_wl_ioctl_cmd(dhd, WLC_SET_VAR, iovbuf, sizeof(iovbuf), TRUE, 0);
	if (ret) {
		DHD_ERROR(("[WIFI_SEC] %s: Fail to execute dhd_wl_ioctl_cmd(): rxchain, ret=%d\n",
			__FUNCTION__, ret));
		return ret;
	}

	return 0;
}
#endif /* MIMO_ANTENNA_SETTING */

#ifdef RSDB_MODE_FROM_FILE
/*
 * RSDBOFFINFO = /data/.rsdb.info
 *  - rsdb_mode = 1            => Don't change RSDB mode / RSDB stay as turn on
 *  - rsdb_mode = 0            => Trun Off RSDB mode
 *  - file not exist          => Don't change RSDB mode / RSDB stay as turn on
 */
int dhd_rsdb_mode_from_file(dhd_pub_t *dhd)
{
	struct file *fp = NULL;
	int ret = -1;
	uint32 rsdb_mode = 0;
	char *filepath = RSDBINFO;
	char iovbuf[WLC_IOCTL_SMLEN];

	/* Read RSDB on/off request from the file */
	fp = filp_open(filepath, O_RDONLY, 0);
	if (IS_ERR(fp)) {
		DHD_ERROR(("[WIFI_SEC] %s: File [%s] doesn't exist\n", __FUNCTION__, filepath));
		return ret;
	} else {
		ret = kernel_read(fp, 0, (char *)&rsdb_mode, 4);
		if (ret < 0) {
			DHD_ERROR(("[WIFI_SEC] %s: File read error, ret=%d\n", __FUNCTION__, ret));
			filp_close(fp, NULL);
			return ret;
		}

		rsdb_mode = bcm_atoi((char *)&rsdb_mode);

		DHD_ERROR(("[WIFI_SEC] %s: RSDB mode from file = %d\n", __FUNCTION__, rsdb_mode));
		filp_close(fp, NULL);

		/* Check value from the file */
		if (rsdb_mode > 2) {
			DHD_ERROR(("[WIFI_SEC] %s: Invalid value %d read from the file %s\n",
				__FUNCTION__, rsdb_mode, filepath));
			return -1;
		}
	}

	if (rsdb_mode == 0) {
		bcm_mkiovar("rsdb_mode", (char *)&rsdb_mode, sizeof(rsdb_mode),
			iovbuf, sizeof(iovbuf));

		if ((ret = dhd_wl_ioctl_cmd(dhd, WLC_SET_VAR,
				iovbuf, sizeof(iovbuf), TRUE, 0)) < 0) {
			DHD_ERROR(("[WIFI_SEC] %s: rsdb_mode ret= %d\n", __FUNCTION__, ret));
		} else {
			DHD_ERROR(("[WIFI_SEC] %s: rsdb_mode to MIMO(RSDB OFF) succeeded\n",
				__FUNCTION__));
		}
	}

	return ret;
}
#endif /* RSDB_MODE_FROM_FILE */

#ifdef LOGTRACE_FROM_FILE
/*
 * LOGTRACEINFO = /data/.logtrace.info
 *  - logtrace = 1            => Enable LOGTRACE Event
 *  - logtrace = 0            => Disable LOGTRACE Event
 *  - file not exist          => Disable LOGTRACE Event
 */
int dhd_logtrace_from_file(dhd_pub_t *dhd)
{
	struct file *fp = NULL;
	int ret = -1;
	uint32 logtrace = 0;
	char *filepath = LOGTRACEINFO;

	/* Read LOGTRACE Event on/off request from the file */
	fp = filp_open(filepath, O_RDONLY, 0);
	if (IS_ERR(fp)) {
		DHD_ERROR(("[WIFI_SEC] %s: File [%s] doesn't exist\n", __FUNCTION__, filepath));
		return 0;
	} else {
		ret = kernel_read(fp, 0, (char *)&logtrace, 4);
		if (ret < 0) {
			DHD_ERROR(("[WIFI_SEC] %s: File read error, ret=%d\n", __FUNCTION__, ret));
			filp_close(fp, NULL);
			return 0;
		}

		logtrace = bcm_atoi((char *)&logtrace);

		DHD_ERROR(("[WIFI_SEC] %s: LOGTRACE On/Off from file = %d\n",
			__FUNCTION__, logtrace));
		filp_close(fp, NULL);

		/* Check value from the file */
		if (logtrace > 2) {
			DHD_ERROR(("[WIFI_SEC] %s: Invalid value %d read from the file %s\n",
				__FUNCTION__, logtrace, filepath));
			return 0;
		}
	}

	return (int)logtrace;
}
#endif /* LOGTRACE_FROM_FILE */

#ifdef USE_WFA_CERT_CONF
int sec_get_param_wfa_cert(dhd_pub_t *dhd, int mode, uint* read_val)
{
	struct file *fp = NULL;
	char *filepath = NULL;
	int val = 0;

	if (!dhd || (mode < SET_PARAM_BUS_TXGLOM_MODE) ||
		(mode >= PARAM_LAST_VALUE)) {
		DHD_ERROR(("[WIFI_SEC] %s: invalid argument\n", __FUNCTION__));
		return BCME_ERROR;
	}

	switch (mode) {
		case SET_PARAM_BUS_TXGLOM_MODE:
			filepath = "/data/.bustxglom.info";
			break;
		case SET_PARAM_ROAMOFF:
			filepath = "/data/.roamoff.info";
			break;
#ifdef USE_WL_FRAMEBURST
		case SET_PARAM_FRAMEBURST:
			filepath = "/data/.frameburst.info";
			break;
#endif /* USE_WL_FRAMEBURST */
#ifdef USE_WL_TXBF
		case SET_PARAM_TXBF:
			filepath = "/data/.txbf.info";
			break;
#endif /* USE_WL_TXBF */
#ifdef PROP_TXSTATUS
		case SET_PARAM_PROPTX:
			filepath = "/data/.proptx.info";
			break;
#endif /* PROP_TXSTATUS */
		default:
			DHD_ERROR(("[WIFI_SEC] %s: File to find file name for index=%d\n",
				__FUNCTION__, mode));
			return BCME_ERROR;
	}

	fp = filp_open(filepath, O_RDONLY, 0);
	if (IS_ERR(fp) || (fp == NULL)) {
		DHD_ERROR(("[WIFI_SEC] %s: File [%s] doesn't exist \n",
			__FUNCTION__, filepath));
		return BCME_ERROR;
	} else {
		if (kernel_read(fp, fp->f_pos, (char *)&val, 4) < 0) {
			filp_close(fp, NULL);
			/* File operation is failed so we will return error code */
			DHD_ERROR(("[WIFI_SEC] %s: read failed, file path=%s\n",
				__FUNCTION__, filepath));
			return BCME_ERROR;
		}
		filp_close(fp, NULL);
	}

	val = bcm_atoi((char *)&val);

	switch (mode) {
		case SET_PARAM_ROAMOFF:
#ifdef USE_WL_FRAMEBURST
		case SET_PARAM_FRAMEBURST:
#endif /* USE_WL_FRAMEBURST */
#ifdef USE_WL_TXBF
		case SET_PARAM_TXBF:
#endif /* USE_WL_TXBF */
#ifdef PROP_TXSTATUS
		case SET_PARAM_PROPTX:
#endif /* PROP_TXSTATUS */
		if (val < 0 || val > 1) {
			DHD_ERROR(("[WIFI_SEC] %s: value[%d] is out of range\n",
				__FUNCTION__, *read_val));
			return BCME_ERROR;
		}
			break;
		default:
			return BCME_ERROR;
	}
	*read_val = (uint)val;
	return BCME_OK;
}
#endif /* USE_WFA_CERT_CONF */
#ifdef WRITE_WLANINFO
#define FIRM_PREFIX "Firm_ver:"
#define DHD_PREFIX "DHD_ver:"
#define NV_PREFIX "Nv_info:"
#define max_len(a, b) ((sizeof(a)/(2)) - (strlen(b)) - (3))
#define tstr_len(a, b) ((strlen(a)) + (strlen(b)) + (3))

char version_info[512];
char version_old_info[512];

int write_filesystem(struct file *file, unsigned long long offset,
	unsigned char* data, unsigned int size)
{
	mm_segment_t oldfs;
	int ret;

	oldfs = get_fs();
	set_fs(get_ds());

	ret = vfs_write(file, data, size, &offset);

	set_fs(oldfs);
	return ret;
}

uint32 sec_save_wlinfo(char *firm_ver, char *dhd_ver, char *nvram_p)
{
	struct file *fp = NULL;
	struct file *nvfp = NULL;
	char *filepath = WIFIVERINFO;
	int min_len, str_len = 0;
	int ret = 0;
	char* nvram_buf;
	char temp_buf[256];

	DHD_TRACE(("[WIFI_SEC] %s: Entered.\n", __FUNCTION__));

	DHD_INFO(("[WIFI_SEC] firmware version   : %s\n", firm_ver));
	DHD_INFO(("[WIFI_SEC] dhd driver version : %s\n", dhd_ver));
	DHD_INFO(("[WIFI_SEC] nvram path : %s\n", nvram_p));

	memset(version_info, 0, sizeof(version_info));

	if (strlen(dhd_ver)) {
		min_len = min(strlen(dhd_ver), max_len(temp_buf, DHD_PREFIX));
		min_len += strlen(DHD_PREFIX) + 3;
		DHD_INFO(("[WIFI_SEC] DHD ver length : %d\n", min_len));
		snprintf(version_info+str_len, min_len, DHD_PREFIX " %s\n", dhd_ver);
		str_len = strlen(version_info);

		DHD_INFO(("[WIFI_SEC] Driver version_info len : %d\n", str_len));
		DHD_INFO(("[WIFI_SEC] Driver version_info : %s\n", version_info));
	} else {
		DHD_ERROR(("[WIFI_SEC] Driver version is missing.\n"));
	}

	if (strlen(firm_ver)) {
		min_len = min(strlen(firm_ver), max_len(temp_buf, FIRM_PREFIX));
		min_len += strlen(FIRM_PREFIX) + 3;
		DHD_INFO(("[WIFI_SEC] firmware ver length : %d\n", min_len));
		snprintf(version_info+str_len, min_len, FIRM_PREFIX " %s\n", firm_ver);
		str_len = strlen(version_info);

		DHD_INFO(("[WIFI_SEC] Firmware version_info len : %d\n", str_len));
		DHD_INFO(("[WIFI_SEC] Firmware version_info : %s\n", version_info));
	} else {
		DHD_ERROR(("[WIFI_SEC] Firmware version is missing.\n"));
	}

	if (nvram_p) {
		memset(temp_buf, 0, sizeof(temp_buf));
		nvfp = filp_open(nvram_p, O_RDONLY, 0);
		if (IS_ERR(nvfp) || (nvfp == NULL)) {
			DHD_ERROR(("[WIFI_SEC] %s: Nvarm File open failed.\n", __FUNCTION__));
			return -1;
		} else {
			ret = kernel_read(nvfp, nvfp->f_pos, temp_buf, sizeof(temp_buf));
			filp_close(nvfp, NULL);
		}

		if (strlen(temp_buf)) {
			nvram_buf = temp_buf;
			bcmstrtok(&nvram_buf, "\n", 0);
			DHD_INFO(("[WIFI_SEC] nvram tolkening : %s(%zu) \n",
				temp_buf, strlen(temp_buf)));
			snprintf(version_info+str_len, tstr_len(temp_buf, NV_PREFIX),
				NV_PREFIX " %s\n", temp_buf);
			str_len = strlen(version_info);
			DHD_INFO(("[WIFI_SEC] NVRAM version_info : %s\n", version_info));
			DHD_INFO(("[WIFI_SEC] NVRAM version_info len : %d, nvram len : %zu\n",
				str_len, strlen(temp_buf)));
		} else {
			DHD_ERROR(("[WIFI_SEC] NVRAM info is missing.\n"));
		}
	} else {
		DHD_ERROR(("[WIFI_SEC] Not exist nvram path\n"));
	}

	DHD_INFO(("[WIFI_SEC] version_info : %s, strlen : %zu\n",
		version_info, strlen(version_info)));

	fp = filp_open(filepath, O_RDONLY, 0);
	if (IS_ERR(fp) || (fp == NULL)) {
		DHD_ERROR(("[WIFI_SEC] %s: .wifiver.info File open failed.\n", __FUNCTION__));
	} else {
		memset(version_old_info, 0, sizeof(version_old_info));
		ret = kernel_read(fp, fp->f_pos, version_old_info, sizeof(version_info));
		filp_close(fp, NULL);
		DHD_INFO(("[WIFI_SEC] kernel_read ret : %d.\n", ret));
		if (strcmp(version_info, version_old_info) == 0) {
			DHD_ERROR(("[WIFI_SEC] .wifiver.info already saved.\n"));
			return 0;
		}
	}

	fp = filp_open(filepath, O_RDWR | O_CREAT, 0664);
	if (IS_ERR(fp) || (fp == NULL)) {
		DHD_ERROR(("[WIFI_SEC] %s: .wifiver.info File open failed.\n",
			__FUNCTION__));
	} else {
		ret = write_filesystem(fp, fp->f_pos, version_info, sizeof(version_info));
		DHD_INFO(("[WIFI_SEC] sec_save_wlinfo done. ret : %d\n", ret));
		DHD_ERROR(("[WIFI_SEC] save .wifiver.info file.\n"));
		filp_close(fp, NULL);
	}
	return ret;
}
#endif /* WRITE_WLANINFO */

#if defined(SUPPORT_MULTIPLE_MODULE_CIS) && defined(USE_CID_CHECK)
int dhd_check_module_b85a(dhd_pub_t *dhd)
{
	int ret = -1;
	struct file *fp = NULL;
	char vname[MAX_VNAME_LEN] = {0, };
	char *vname_b85a = "_b85a";
	const char *cidfilepath = CIDINFO;
	const char *s = NULL;

	fp = filp_open(cidfilepath, O_RDONLY, 0);
	if (IS_ERR(fp) || (fp == NULL)) {
		DHD_ERROR(("[WIFI_SEC] %s: %s File open failed.\n", __FUNCTION__, cidfilepath));
		ret = -1;
	} else {
		ret = kernel_read(fp, fp->f_pos, vname, sizeof(vname));
		if (ret < 0) {
			DHD_ERROR(("[WIFI_SEC] %s: File read error, ret=%d \n", __FUNCTION__, ret));
			filp_close(fp, NULL);
			return ret;
		}

		DHD_ERROR(("[WIFI_SEC] %s: This module is %s \n", __FUNCTION__, vname));
		filp_close(fp, NULL);

		s = strstr(vname, vname_b85a);
		if (s != NULL) {
			DHD_INFO(("[WIFI_SEC] %s: It's a b85a module \n", __FUNCTION__));
			ret = 1;
		} else {
			DHD_INFO(("[WIFI_SEC] %s: It is not a b85a module \n", __FUNCTION__));
			ret = -1;
		}
	}

	return ret;
}

int
dhd_check_module_b90(dhd_pub_t *dhd)
{
	int ret = BCME_ERROR;
	struct file *fp = NULL;
	char vname[MAX_VNAME_LEN] = {0, };
	char *vname_b90b = "_b90b";
	char *vname_b90s = "_b90s";
	const char *cidfilepath = CIDINFO;
	const char *s = NULL;

	fp = filp_open(cidfilepath, O_RDONLY, 0);

	if (IS_ERR(fp) || (fp == NULL)) {
		DHD_ERROR(("[WIFI_SEC] %s: %s File open failed.\n", __FUNCTION__, cidfilepath));
		ret = BCME_ERROR;
	} else {
		ret = kernel_read(fp, fp->f_pos, vname, sizeof(vname));
		if (ret < 0) {
			DHD_ERROR(("[WIFI_SEC] %s: File read error, ret=%d \n", __FUNCTION__, ret));
			filp_close(fp, NULL);
			return ret;
		}

		DHD_ERROR(("[WIFI_SEC] %s: This module is %s \n", __FUNCTION__, vname));
		filp_close(fp, NULL);

		s = strstr(vname, vname_b90b);
		if (s != NULL) {
			DHD_INFO(("[WIFI_SEC] %s: It's a b90b module \n", __FUNCTION__));
			ret = BCM4359_MODULE_TYPE_B90B;
			return ret;
		}

		s = strstr(vname, vname_b90s);
		if (s != NULL) {
			DHD_INFO(("[WIFI_SEC] %s: It's a b90s module \n", __FUNCTION__));
			ret = BCM4359_MODULE_TYPE_B90S;
		} else {
			DHD_ERROR(("[WIFI_SEC] %s: It's neither b90b nor b90s \n",
				__FUNCTION__));
			ret = BCME_ERROR;
		}
	}

	return ret;
}
#endif /* defined(SUPPORT_MULTIPLE_MODULE_CIS) && defined(USE_CID_CHECK) */
#endif /* CUSTOMER_HW4 || CUSTOMER_HW40 */

#if defined(FORCE_DISABLE_SINGLECORE_SCAN)
void
dhd_force_disable_singlcore_scan(dhd_pub_t *dhd)
{
	int ret = 0;
	struct file *fp = NULL;
	char *filepath = "/data/.cid.info";
	s8 iovbuf[WL_EVENTING_MASK_LEN + 12];
	char vender[10] = {0, };
	uint32 pm_bcnrx = 0;
	uint32 scan_ps = 0;

	if (BCM4354_CHIP_ID != dhd_bus_chip_id(dhd))
		return;

	fp = filp_open(filepath, O_RDONLY, 0);
	if (IS_ERR(fp)) {
		DHD_ERROR(("/data/.cid.info file open error\n"));
	} else {
		ret = kernel_read(fp, 0, (char *)vender, 5);

		if (ret > 0 && NULL != strstr(vender, "wisol")) {
			DHD_ERROR(("wisol module : set pm_bcnrx=0, set scan_ps=0\n"));

			bcm_mkiovar("pm_bcnrx", (char *)&pm_bcnrx, 4, iovbuf, sizeof(iovbuf));
			ret = dhd_wl_ioctl_cmd(dhd, WLC_SET_VAR, iovbuf, sizeof(iovbuf), TRUE, 0);
			if (ret < 0)
				DHD_ERROR(("Set pm_bcnrx error (%d)\n", ret));

			bcm_mkiovar("scan_ps", (char *)&scan_ps, 4, iovbuf, sizeof(iovbuf));
			ret = dhd_wl_ioctl_cmd(dhd, WLC_SET_VAR, iovbuf, sizeof(iovbuf), TRUE, 0);
			if (ret < 0)
				DHD_ERROR(("Set scan_ps error (%d)\n", ret));
		}
		filp_close(fp, NULL);
	}
}
#endif /* FORCE_DISABLE_SINGLECORE_SCAN */
