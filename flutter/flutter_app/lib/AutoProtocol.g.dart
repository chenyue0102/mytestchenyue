// GENERATED CODE - DO NOT MODIFY BY HAND

part of 'AutoProtocol.dart';

// **************************************************************************
// JsonSerializableGenerator
// **************************************************************************

AutoProtocol _$AutoProtocolFromJson(Map<String, dynamic> json) {
  return AutoProtocol(
    json['slideshow'] == null
        ? null
        : SliderShow.fromJson(json['slideshow'] as Map<String, dynamic>),
  );
}

Map<String, dynamic> _$AutoProtocolToJson(AutoProtocol instance) =>
    <String, dynamic>{
      'slideshow': instance.slideshow,
    };

SliderShow _$SliderShowFromJson(Map<String, dynamic> json) {
  return SliderShow(
    json['author'] as String,
    json['date'] as String,
    (json['slides'] as List)
        ?.map(
            (e) => e == null ? null : Slide.fromJson(e as Map<String, dynamic>))
        ?.toList(),
    json['title'] as String,
  );
}

Map<String, dynamic> _$SliderShowToJson(SliderShow instance) =>
    <String, dynamic>{
      'author': instance.author,
      'date': instance.date,
      'slides': instance.slides,
      'title': instance.title,
    };

Slide _$SlideFromJson(Map<String, dynamic> json) {
  return Slide(
    json['title'] as String,
    json['type'] as String,
    (json['items'] as List)?.map((e) => e as String)?.toList(),
  );
}

Map<String, dynamic> _$SlideToJson(Slide instance) => <String, dynamic>{
      'title': instance.title,
      'type': instance.type,
      'items': instance.items,
    };
