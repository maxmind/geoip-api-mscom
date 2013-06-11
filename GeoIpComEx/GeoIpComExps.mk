
GeoIpComExps.dll: dlldata.obj GeoIpComEx_p.obj GeoIpComEx_i.obj
	link /dll /out:GeoIpComExps.dll /def:GeoIpComExps.def /entry:DllMain dlldata.obj GeoIpComEx_p.obj GeoIpComEx_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del GeoIpComExps.dll
	@del GeoIpComExps.lib
	@del GeoIpComExps.exp
	@del dlldata.obj
	@del GeoIpComEx_p.obj
	@del GeoIpComEx_i.obj
