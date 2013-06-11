// GeoIPEx.h : Declaration of the CGeoIPEx

#ifndef __GEOIPEX_H_
#define __GEOIPEX_H_

#include "resource.h"       // main symbols
#include "libGeoIP\GeoIP.h" 
#include "libGeoIP\GeoIPCity.h" 


/////////////////////////////////////////////////////////////////////////////
// CGeoIPEx
class ATL_NO_VTABLE CGeoIPEx : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CGeoIPEx, &CLSID_GeoIPEx>,
	public IDispatchImpl<IGeoIPEx, &IID_IGeoIPEx, &LIBID_GEOIPCOMEXLib>
{
public:
	CGeoIPEx()
	{
		f_error_msg = L"DB directory not set";
		country_db = NULL;
		region_db = NULL;
		city_db = NULL;
		org_db = NULL;
		isp_db = NULL;
		asnum_db = NULL;
		domain_db = NULL;
		wsa_init = FALSE;
	}

	~CGeoIPEx()
	{
		clear_db();
	}

DECLARE_REGISTRY_RESOURCEID(IDR_GEOIPEX)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CGeoIPEx)
	COM_INTERFACE_ENTRY(IGeoIPEx)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IGeoIPEx
public:
	STDMETHOD(get_supports_position)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_supports_postal_code)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_supports_dma_code)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_supports_region)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_supports_area_code)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_error_msg)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_supports_country_code3)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_supports_asnum)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_supports_domain)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_supports_ISP)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_supports_organization)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_supports_city)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_supports_country_name)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_supports_country_code)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_organization)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_ISP)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_area_code)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_dma_code)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_longitude)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_latitude)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_postal_code)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_city)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_region)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_country_name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_country_code3)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_country_code)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(set_db_path)(/*[in]*/ BSTR newVal, /*[out,retval]*/ VARIANT_BOOL *present);
	STDMETHOD(find_by_name)(/*[in]*/ BSTR ip_address, /*[out,retval]*/ VARIANT_BOOL *found);
	STDMETHOD(find_by_addr)(/*[in]*/ BSTR ip_address, /*[out,retval]*/ VARIANT_BOOL *found);
private:
	CComBSTR db_path;
	CComBSTR f_country_code;
	CComBSTR f_country_code3;
	CComBSTR f_country_name;
	CComBSTR f_city;
	CComBSTR f_region;
	CComBSTR f_postal_code;
	CComBSTR f_org;
	CComBSTR f_isp;
	CComBSTR f_domain;
	CComBSTR f_asnum;
	double f_longitude;
	double f_latitude;
	long f_area_code;
	long f_dma_code;
	CComBSTR f_error_msg;

	GeoIP *country_db;
	GeoIP *region_db;
	GeoIP *city_db;
	GeoIP *org_db;
	GeoIP *isp_db;
	GeoIP *domain_db;
	GeoIP *asnum_db;

	bool wsa_init;

	void clear_db();
	bool find_ip(LPCSTR addr, bool byname);

};

#endif //__GEOIPEX_H_
