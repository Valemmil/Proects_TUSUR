from django.http import HttpResponse
from currency import forms
from django.shortcuts import render
import requests
import json


def convert_currency(request):
    """ Конвертируем с одной валюты в другую"""

    # апишка

    url = "https://api.apilayer.com/fixer/convert?to=to&from=from&amount=amount"

    payload = {}
    headers = {
        "apikey": "sppMDWVO5HwSfUXY7LMd1AshnKYM7aqG"
    }

    api_request = requests.request("GET", url, headers=headers, data=payload)
    currency_dict = json.loads(api_request.text)

    # currency_rates_dict = currency_dict['rates']
    currency_rates_dict = {}
    list_of_country_currency_code = [x for x in currency_rates_dict.keys()]
    tuple_of_country_codes = [tuple([x, x]) for x in list_of_country_currency_code]

    # инициализация формы
    currency_form = forms.CurrencyForm(tuple_of_country_codes, request.POST or None)

    converted_currency = ""
    if request.method == "POST":
        # проверка
        if currency_form.is_valid():
            # значения с html
            source_currency_code = currency_form.cleaned_data['source_currency_code']
            target_currency_code = currency_form.cleaned_data['target_currency_code']
            input_currency_value = currency_form.cleaned_data['source_currency_value']

            # Получаем текущее значение валюты 
            from_country_base_value = currency_rates_dict[source_currency_code]
            to_country_base_value = currency_rates_dict[target_currency_code]

            # Формула конвертации
            converted_currency = (to_country_base_value / from_country_base_value) * float(input_currency_value)

            return render(request, 'currency/currency-index.html',
                          {'currency_form': currency_form, 'converted_currency': f"{converted_currency:.2f}"})

    # Инициализация формы
    context = {
        'currency_form': currency_form,
        'converted_currency': converted_currency
    }
    return render(request, 'currency/currency-index.html', context)
