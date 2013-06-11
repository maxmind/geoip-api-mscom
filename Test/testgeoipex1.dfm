object Form1: TForm1
  Left = 226
  Top = 91
  Width = 813
  Height = 452
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 156
    Top = 168
    Width = 52
    Height = 13
    Caption = 'DNS-name'
  end
  object Label2: TLabel
    Left = 460
    Top = 168
    Width = 50
    Height = 13
    Caption = 'IP-address'
  end
  object Label3: TLabel
    Left = 72
    Top = 256
    Width = 63
    Height = 13
    Caption = 'Country code'
  end
  object Label4: TLabel
    Left = 264
    Top = 256
    Width = 30
    Height = 13
    Caption = 'code3'
  end
  object Label5: TLabel
    Left = 432
    Top = 256
    Width = 28
    Height = 13
    Caption = 'Name'
  end
  object Label6: TLabel
    Left = 72
    Top = 308
    Width = 34
    Height = 13
    Caption = 'Region'
  end
  object Label7: TLabel
    Left = 264
    Top = 308
    Width = 17
    Height = 13
    Caption = 'City'
  end
  object Label8: TLabel
    Left = 432
    Top = 308
    Width = 45
    Height = 13
    Caption = 'Postcode'
  end
  object Label9: TLabel
    Left = 268
    Top = 348
    Width = 15
    Height = 13
    Caption = 'Lat'
  end
  object Label10: TLabel
    Left = 268
    Top = 388
    Width = 24
    Height = 13
    Caption = 'Long'
  end
  object Label11: TLabel
    Left = 432
    Top = 348
    Width = 46
    Height = 13
    Caption = 'Areacode'
  end
  object Label12: TLabel
    Left = 432
    Top = 388
    Width = 46
    Height = 13
    Caption = 'Dmacode'
  end
  object Label13: TLabel
    Left = 72
    Top = 348
    Width = 59
    Height = 13
    Caption = 'Organization'
  end
  object Label14: TLabel
    Left = 72
    Top = 388
    Width = 17
    Height = 13
    Caption = 'ISP'
  end
  object Edit_dns: TEdit
    Left = 156
    Top = 184
    Width = 189
    Height = 21
    TabOrder = 0
    Text = 'www.yahoo.com'
  end
  object Button1: TButton
    Left = 60
    Top = 28
    Width = 75
    Height = 25
    Caption = 'Set DB dir'
    TabOrder = 1
    OnClick = Load_file
  end
  object Button2: TButton
    Left = 60
    Top = 180
    Width = 85
    Height = 25
    Caption = 'Lookup Name'
    TabOrder = 2
    OnClick = name_to_code
  end
  object edit_filename: TEdit
    Left = 152
    Top = 32
    Width = 609
    Height = 21
    TabOrder = 3
    Text = 'c:\Projects\geoipmscomapi\geo\Geoipcomex\data'
  end
  object Edit_ip: TEdit
    Left = 460
    Top = 184
    Width = 189
    Height = 21
    TabOrder = 4
    Text = '212.112.41.67'
  end
  object res_cc: TEdit
    Left = 156
    Top = 252
    Width = 89
    Height = 21
    ReadOnly = True
    TabOrder = 5
  end
  object Button5: TButton
    Left = 364
    Top = 180
    Width = 89
    Height = 25
    Caption = 'Lookup Address'
    TabOrder = 6
    OnClick = addr_to_code
  end
  object res_cc3: TEdit
    Left = 312
    Top = 252
    Width = 89
    Height = 21
    ReadOnly = True
    TabOrder = 7
  end
  object res_cn: TEdit
    Left = 508
    Top = 252
    Width = 253
    Height = 21
    ReadOnly = True
    TabOrder = 8
  end
  object res_reg: TEdit
    Left = 156
    Top = 304
    Width = 89
    Height = 21
    ReadOnly = True
    TabOrder = 9
  end
  object res_city: TEdit
    Left = 312
    Top = 304
    Width = 89
    Height = 21
    ReadOnly = True
    TabOrder = 10
  end
  object res_pc: TEdit
    Left = 508
    Top = 304
    Width = 177
    Height = 21
    ReadOnly = True
    TabOrder = 11
  end
  object res_lat: TEdit
    Left = 312
    Top = 344
    Width = 89
    Height = 21
    ReadOnly = True
    TabOrder = 12
  end
  object res_long: TEdit
    Left = 312
    Top = 384
    Width = 89
    Height = 21
    ReadOnly = True
    TabOrder = 13
  end
  object cb_supp_cc: TCheckBox
    Left = 156
    Top = 76
    Width = 153
    Height = 17
    Caption = 'Supports Country code'
    Enabled = False
    TabOrder = 14
  end
  object cb_supp_cn: TCheckBox
    Left = 156
    Top = 100
    Width = 145
    Height = 17
    Caption = 'Supports Country Name'
    Enabled = False
    TabOrder = 15
  end
  object cb_supp_city: TCheckBox
    Left = 368
    Top = 76
    Width = 97
    Height = 17
    Caption = 'Supports City'
    Enabled = False
    TabOrder = 16
  end
  object cb_supp_isp: TCheckBox
    Left = 496
    Top = 76
    Width = 97
    Height = 17
    Caption = 'Supports ISP'
    Enabled = False
    TabOrder = 17
  end
  object cb_supp_org: TCheckBox
    Left = 496
    Top = 100
    Width = 137
    Height = 17
    Caption = 'Supports Organization'
    Enabled = False
    TabOrder = 18
  end
  object cb_supp_region: TCheckBox
    Left = 368
    Top = 100
    Width = 97
    Height = 17
    Caption = 'Supports region'
    Enabled = False
    TabOrder = 19
  end
  object res_area: TEdit
    Left = 508
    Top = 344
    Width = 89
    Height = 21
    ReadOnly = True
    TabOrder = 20
  end
  object res_dma: TEdit
    Left = 508
    Top = 384
    Width = 89
    Height = 21
    ReadOnly = True
    TabOrder = 21
  end
  object res_org: TEdit
    Left = 156
    Top = 344
    Width = 89
    Height = 21
    ReadOnly = True
    TabOrder = 22
  end
  object res_isp: TEdit
    Left = 156
    Top = 384
    Width = 89
    Height = 21
    ReadOnly = True
    TabOrder = 23
  end
  object res_sts: TEdit
    Left = 680
    Top = 184
    Width = 81
    Height = 21
    ReadOnly = True
    TabOrder = 24
  end
end
