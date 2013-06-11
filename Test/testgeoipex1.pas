unit testgeoipex1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    Edit_dns: TEdit;
    Button1: TButton;
    Button2: TButton;
    edit_filename: TEdit;
    Label1: TLabel;
    Edit_ip: TEdit;
    Label2: TLabel;
    res_cc: TEdit;
    Button5: TButton;
    Label3: TLabel;
    res_cc3: TEdit;
    Label4: TLabel;
    res_cn: TEdit;
    Label5: TLabel;
    res_reg: TEdit;
    Label6: TLabel;
    res_city: TEdit;
    Label7: TLabel;
    res_pc: TEdit;
    Label8: TLabel;
    res_lat: TEdit;
    Label9: TLabel;
    res_long: TEdit;
    Label10: TLabel;
    cb_supp_cc: TCheckBox;
    cb_supp_cn: TCheckBox;
    cb_supp_city: TCheckBox;
    cb_supp_isp: TCheckBox;
    cb_supp_org: TCheckBox;
    cb_supp_region: TCheckBox;
    res_area: TEdit;
    Label11: TLabel;
    res_dma: TEdit;
    Label12: TLabel;
    res_org: TEdit;
    Label13: TLabel;
    res_isp: TEdit;
    Label14: TLabel;
    res_sts: TEdit;
    procedure Load_file(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure name_to_code(Sender: TObject);
    procedure addr_to_code(Sender: TObject);
  private
      GeoIP: OLEVariant;
    procedure show;
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation
{$R *.dfm}

  uses comobj,ActiveX;

  procedure Tform1.Load_file(Sender: TObject);
    var b: olevariant; i:integer;
    begin
      b:=GeoIP.set_db_path(edit_filename.text);
//      b:=i;
      if b then
        res_sts.text:= 'OK'
      else
        res_sts.text:= 'Not all dbs found';

        //now we can check support info etc
        cb_supp_cc.Checked   := GeoIP.supports_country_code;
        cb_supp_cn.Checked   := GeoIP.supports_country_name;
        cb_supp_city.Checked := GeoIP.supports_city;
        cb_supp_org.Checked  := GeoIP.supports_organization;
        cb_supp_isp.Checked  := GeoIP.supports_ISP;
        cb_supp_region.Checked  := GeoIP.supports_region;
    end;

procedure TForm1.FormCreate(Sender: TObject);
  begin
//  GeoIP := CreateOleObject('GeoIPCom.GeoIP');
    GeoIP := CreateOleObject('GeoIPComEx.GeoIPEx');
  end;


procedure TForm1.show;
  begin
    res_cc.Text  := GeoIP.country_code;
    res_cc3.Text := GeoIP.country_code3;
    res_cn.Text  := GeoIP.country_name;
    res_city.Text:= GeoIP.city;
    res_reg.Text := GeoIP.region;
    res_pc.Text  := GeoIP.postal_code;
    res_lat.Text := GeoIP.latitude;
    res_long.Text:= GeoIP.longitude;
    res_dma.Text := GeoIP.dma_code;
    res_area.Text:= GeoIP.area_code;

    res_org.Text := GeoIP.organization;
    res_isp.Text := GeoIP.ISP;

  end;


procedure TForm1.name_to_code(Sender: TObject);
  begin
    if GeoIP.find_by_name(edit_dns.text) then
      res_sts.text:= 'OK'
    else
      res_sts.text:= 'Not found';
    show;
  end;

procedure TForm1.addr_to_code(Sender: TObject);
  begin
    if GeoIP.find_by_addr(edit_ip.text) then
      res_sts.text:= 'OK'
    else
      res_sts.text:= 'Not found';
    show;
  end;


end.
