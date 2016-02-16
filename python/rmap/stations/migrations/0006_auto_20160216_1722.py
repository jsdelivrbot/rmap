# -*- coding: utf-8 -*-
# Generated by Django 1.9 on 2016-02-16 17:22
from __future__ import unicode_literals

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('stations', '0005_auto_20151128_0940'),
    ]

    operations = [
        migrations.AlterField(
            model_name='sensor',
            name='type',
            field=models.CharField(choices=[(b'TMP', b'I2C TMP temperature sensor'), (b'ADT', b'I2C ADT temperature sensor'), (b'BMP', b'I2C BMP085/BMP180 pressure sensor'), (b'HIH', b'I2C HIH6100 series humidity sensor'), (b'DW1', b'I2C Davis/Inspeed/Windsonic wind direction and intensity adapter'), (b'TBR', b'I2C Tipping bucket rain gauge adapter'), (b'RF24', b'RF24 Network jsonrpc')], default=b'TMP', help_text='Type of sensor', max_length=4),
        ),
    ]
