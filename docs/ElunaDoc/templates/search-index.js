var searchIndex = {};

//{%- for class in classes %}
searchIndex["{{ class.name }}"] = {
    "items": [
        [0, "", "{{ class.name }}", "{{ class.short_description|replace('\n', ' ')|replace('\"', '&#34;') }}"],
        //{%- for method in class.methods %}
        [3, "{{ method.name }}", "", "{{ method.short_description|replace('\n', ' ')|replace('\"', '&#34;') }}"],
        //{%- endfor %}
    ],
    "paths": [

    ]
};
//{%- endfor %}

initSearch(searchIndex);