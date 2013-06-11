/* GeoIPEx.cpp : Implementation of CGeoIPEx
 *
 * Copyright (C) 2012 MaxMind, Inc.  All Rights Reserved.
 */



#include "stdafx.h"
#include "GeoIpComEx.h"
#include "GeoIPEx.h"

/////////////////////////////////////////////////////////////////////////////
// CGeoIPEx, a COM object wrapper for Maxmind GeoIP library
/////////////////////////////////////////////////////////////////////////////

//to avoid the hardcoded GEODATADIR in geoip.c, we never use GeoIP_open_type() etc
//so we duplicate some db filenames here
#define COUNTRY_FN L"/GeoIP.dat";
#define REGION_FN L"/GeoIPRegion.dat";
#define CITY_FN L"/GeoIPCity.dat";
#define ORG_FN  L"/GeoIPOrg.dat";
#define ISP_FN  L"/GeoIPISP.dat";
#define ASNUM_FN  L"/GeoIPASNum.dat";
#define DOMAIN_FN  L"/GeoIPDomain.dat";


// find_ip()
// Internal general data retrieval procedure
// called by the find_by_addr() and find_by_name() methods

bool CGeoIPEx::find_ip(LPCSTR addr, bool byname)
{
	USES_CONVERSION;

	bool found_city = false;
	bool found_region = false;

	if (city_db) {
		//lookup city record
		GeoIPRecord* r;
		if (byname)
			r = GeoIP_record_by_name(city_db,addr);
		else
			r = GeoIP_record_by_addr(city_db,addr);

		found_city = (r != NULL);
		if (found_city) {
			//copy property values
			f_country_code  = r->country_code;
			f_country_code3 = r->country_code3;
			f_country_name  = r->country_name;
			f_city          = r->city;
			f_region        = r->region;
			f_postal_code   = r->postal_code;
			f_area_code     = r->area_code;
			f_dma_code      = r->dma_code;
			f_longitude     = r->longitude;
			f_latitude      = r->latitude;
			//drop city record
			GeoIPRecord_delete(r);
		}
	}

	if (!found_city) { // not found or no db
		// empty all property storage fields
		f_country_code.Empty();
		f_country_code3.Empty();
		f_country_name.Empty();
		f_city.Empty();
		f_region.Empty();
		f_postal_code.Empty();
		f_area_code = 0;
		f_dma_code = 0;
		f_latitude = 0.0;
		f_longitude = 0.0;

		if (region_db) {
			GeoIPRegion *region;
			if (byname)
				region = GeoIP_region_by_name(region_db,addr);
			else
				region = GeoIP_region_by_addr(region_db,addr);
			found_region = (region != NULL);

			if (found_region) {
				f_country_code = region->country_code;
				f_region = region->region;
			}
		}

		if (!found_region) { // not found or no db
			if (country_db) {
				const char * country;
				if (byname)
					country = GeoIP_country_code_by_name(country_db,addr);
				else
					country = GeoIP_country_code_by_addr(country_db,addr);
				if (country)
					f_country_code = country;
			}
		}
	}
	
	//get org and isp data
	if (org_db) {
		LPSTR s;
		if (byname)
			s = GeoIP_org_by_name (org_db, addr);
		else
			s = GeoIP_org_by_addr (org_db, addr);
		if (s) {
			f_org = s;
			free (s);
		} else f_org.Empty();
	} else f_org.Empty();

	if (isp_db) {
		LPSTR s;
		if (byname)
			s = GeoIP_org_by_name (isp_db, addr);
		else
			s = GeoIP_org_by_addr (isp_db, addr);
		if (s) {
			f_isp = s;
			free (s);
		} else f_isp.Empty();
	} else f_isp.Empty();

	if (domain_db) {
		LPSTR s;
		if (byname)
			s = GeoIP_org_by_name (org_db, addr);
		else
			s = GeoIP_org_by_addr (org_db, addr);
		if (s) {
			f_domain = s;
			free (s);
		} else f_domain.Empty();
	} else f_domain.Empty();

        if (asnum_db) {
		LPSTR s;
		if (byname)
			s = GeoIP_org_by_name (org_db, addr);
		else
			s = GeoIP_org_by_addr (org_db, addr);
		if (s) {
			f_asnum = s;
			free (s);
		} else f_asnum.Empty();
	} else f_asnum.Empty();
	
	return found_city;
	
}


// find_by_addr()
// Returns true if basic (city db) data was found
// note that the VARIANT_TRUE constant must be used
STDMETHODIMP CGeoIPEx::find_by_addr(BSTR ip_address, VARIANT_BOOL *found)
{
	USES_CONVERSION;
	LPSTR s = W2A(ip_address);

	//check for built-in addresses (yech, this should be in database!)
	if (strncmp(s,"10.",     3) == 0 ||
		strncmp(s,"172.16.", 7) == 0 ||
		strncmp(s,"172.17.", 7) == 0 ||
		strncmp(s,"172.18.", 7) == 0 ||
		strncmp(s,"172.19.", 7) == 0 ||
		strncmp(s,"172.20.", 7) == 0 ||
		strncmp(s,"172.21.", 7) == 0 ||
		strncmp(s,"172.22.", 7) == 0 ||
		strncmp(s,"172.23.", 7) == 0 ||
		strncmp(s,"172.24.", 7) == 0 ||
		strncmp(s,"172.25.", 7) == 0 ||
		strncmp(s,"172.26.", 7) == 0 ||
		strncmp(s,"172.27.", 7) == 0 ||
		strncmp(s,"172.28.", 7) == 0 ||
		strncmp(s,"172.29.", 7) == 0 ||
		strncmp(s,"172.30.", 7) == 0 ||
		strncmp(s,"172.31.", 7) == 0 ||
		strncmp(s,"192.168.",8) == 0)
	{
		f_country_code = L"LN";
		f_country_name = L"Local Area Network";
		// empty all other property storage fields
		f_country_code3.Empty();
		f_city.Empty();
		f_region.Empty();
		f_postal_code.Empty();
		f_area_code = 0;
		f_dma_code = 0;
		f_latitude = 0.0;
		f_longitude = 0.0;
		*found = VARIANT_TRUE; //must have all bits set; NOT same as true
	}
	else
	if (strncmp(s,"127.",4) == 0)
	{
		f_country_code = L"LH";
		f_country_name = L"Localhost";
		// empty all other property storage fields
		f_country_code3.Empty();
		f_city.Empty();
		f_region.Empty();
		f_postal_code.Empty();
		f_area_code = 0;
		f_dma_code = 0;
		f_latitude = 0.0;
		f_longitude = 0.0;
		*found = VARIANT_TRUE;
	}
	else

	*found = find_ip(s,FALSE) ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}


STDMETHODIMP CGeoIPEx::find_by_name(BSTR ip_address, VARIANT_BOOL *found)
{
	USES_CONVERSION;

	//initialize winsock if necessary
	if (!wsa_init) {
		WSADATA w;
		int err = WSAStartup(1,&w);
		if (err) {
			char buf[1000];
			sprintf(buf,"WSA initialization error %d",err);
			f_error_msg = buf;
			*found = FALSE;
			return S_OK;
		}
		wsa_init = TRUE;
	}

	*found = find_ip(W2A(ip_address),TRUE) ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}


STDMETHODIMP CGeoIPEx::set_db_path(BSTR newVal, VARIANT_BOOL *present)
{
	USES_CONVERSION;

	clear_db();

	db_path = newVal; //copy the value
	f_error_msg.Empty();

	//open databases
	CComBSTR fn(db_path);
	fn += COUNTRY_FN;
	country_db = GeoIP_open(W2A(fn),GEOIP_STANDARD);

	fn=db_path;
	fn += REGION_FN;
	region_db = GeoIP_open(W2A(fn),GEOIP_STANDARD);

	fn=db_path;
	fn += CITY_FN;
	city_db = GeoIP_open(W2A(fn),GEOIP_STANDARD);

	fn=db_path;
	fn += ORG_FN;
	org_db = GeoIP_open(W2A(fn),GEOIP_STANDARD);

	fn=db_path;
	fn += ISP_FN;
	isp_db = GeoIP_open(W2A(fn),GEOIP_STANDARD);

	fn=db_path;
        fn += ASNUM_FN;
	asnum_db = GeoIP_open(W2A(fn),GEOIP_STANDARD);

        fn=db_path;
	fn += DOMAIN_FN;
	domain_db = GeoIP_open(W2A(fn),GEOIP_STANDARD);

	*present = (city_db && org_db && isp_db)? VARIANT_TRUE : VARIANT_FALSE;;

	return S_OK;
}


STDMETHODIMP CGeoIPEx::get_country_code(BSTR *pVal)
{
	//just copy the value
	return f_country_code.CopyTo(pVal);
}


STDMETHODIMP CGeoIPEx::get_country_code3(BSTR *pVal)
{
	//just copy the value
	return f_country_code3.CopyTo(pVal);
}


STDMETHODIMP CGeoIPEx::get_country_name(BSTR *pVal)
{
	//just copy the value
	return f_country_name.CopyTo(pVal);
}


STDMETHODIMP CGeoIPEx::get_region(BSTR *pVal)
{
	//just copy the value
	return f_region.CopyTo(pVal);
}


STDMETHODIMP CGeoIPEx::get_city(BSTR *pVal)
{
	//just copy the value
	return f_city.CopyTo(pVal);
}


STDMETHODIMP CGeoIPEx::get_postal_code(BSTR *pVal)
{
	//just copy the value
	return f_postal_code.CopyTo(pVal);	
}


STDMETHODIMP CGeoIPEx::get_latitude(double *pVal)
{
	*pVal = f_latitude;
	return S_OK;
}


STDMETHODIMP CGeoIPEx::get_longitude(double *pVal)
{
	*pVal = f_longitude;
	return S_OK;
}


STDMETHODIMP CGeoIPEx::get_dma_code(long *pVal)
{
	*pVal = f_dma_code;
	return S_OK;
}


STDMETHODIMP CGeoIPEx::get_area_code(long *pVal)
{
	*pVal = f_area_code;
	return S_OK;
}


STDMETHODIMP CGeoIPEx::get_ISP(BSTR *pVal)
{
	//just copy the value
	return f_isp.CopyTo(pVal);
}


STDMETHODIMP CGeoIPEx::get_organization(BSTR *pVal)
{
	//just copy the value
	return f_org.CopyTo(pVal);
}


STDMETHODIMP CGeoIPEx::get_supports_country_code(VARIANT_BOOL *pVal)
{
	*pVal = (country_db != NULL || region_db != NULL || city_db != NULL)? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}


STDMETHODIMP CGeoIPEx::get_supports_country_name(VARIANT_BOOL *pVal)
{
	*pVal = (city_db != NULL)? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}


STDMETHODIMP CGeoIPEx::get_supports_city(VARIANT_BOOL *pVal)
{
	*pVal = (city_db != NULL)? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}


STDMETHODIMP CGeoIPEx::get_supports_ISP(VARIANT_BOOL *pVal)
{
	*pVal = (isp_db != NULL)? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}


STDMETHODIMP CGeoIPEx::get_supports_asnum(VARIANT_BOOL *pVal)
{
	*pVal = (asnum_db != NULL)? VARIANT_TRUE : VARIANT_FALSE;

        return S_OK;
}


STDMETHODIMP CGeoIPEx::get_supports_domain(VARIANT_BOOL *pVal)
{
	*pVal = (domain_db != NULL)? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}


STDMETHODIMP CGeoIPEx::get_supports_organization(VARIANT_BOOL *pVal)
{
	*pVal = (org_db != NULL)? VARIANT_TRUE : VARIANT_FALSE;
	
	return S_OK;
}


STDMETHODIMP CGeoIPEx::get_supports_country_code3(VARIANT_BOOL *pVal)
{
	*pVal = (city_db != NULL)? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}


void CGeoIPEx::clear_db()
{
	//get rid of old databases, if any
	if (country_db)
		GeoIP_delete(country_db);
	if (region_db)
		GeoIP_delete(region_db);
	if (city_db)
	  GeoIP_delete(city_db);
	if (org_db)
	  GeoIP_delete(org_db);
	if (isp_db)
	  GeoIP_delete(isp_db);
}	if (asnum_db)
	  GeoIP_delete(asnum_db);
}	if (domain_db)
	  GeoIP_delete(domain_db);
}


STDMETHODIMP CGeoIPEx::get_error_msg(BSTR *pVal)
{
	//just copy the value
	return f_error_msg.CopyTo(pVal);
}


STDMETHODIMP CGeoIPEx::get_supports_area_code(VARIANT_BOOL *pVal)
{
	*pVal = (city_db != NULL)? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}


STDMETHODIMP CGeoIPEx::get_supports_region(VARIANT_BOOL *pVal)
{
	*pVal = (region_db != NULL || city_db != NULL)? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}


STDMETHODIMP CGeoIPEx::get_supports_dma_code(VARIANT_BOOL *pVal)
{
	*pVal = (city_db != NULL)? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}


STDMETHODIMP CGeoIPEx::get_supports_postal_code(VARIANT_BOOL *pVal)
{
	*pVal = (city_db != NULL)? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}


STDMETHODIMP CGeoIPEx::get_supports_position(VARIANT_BOOL *pVal)
{
	*pVal = (city_db != NULL)? VARIANT_TRUE : VARIANT_FALSE;

	return S_OK;
}
