import 'package:json_annotation/json_annotation.dart';

part 'AutoProtocol.g.dart';

@JsonSerializable()
class AutoProtocol{
  AutoProtocol(this.slideshow);

  SliderShow slideshow;

  factory AutoProtocol.fromJson(Map<String, dynamic> json) => _$AutoProtocolFromJson(json);

  Map<String, dynamic> toJson() => _$AutoProtocolToJson(this);
}

@JsonSerializable()
class SliderShow{
  SliderShow(this.author, this.date, this.slides, this.title);

  String author;
  String date;
  List<Slide> slides;
  String title;

  factory SliderShow.fromJson(Map<String, dynamic> json) => _$SliderShowFromJson(json);

  Map<String, dynamic> toJson() => _$SliderShowToJson(this);
}

@JsonSerializable()
class Slide{
  Slide(this.title, this.type, this.items);

  String title;
  String type;
  List<String> items;

  factory Slide.fromJson(Map<String, dynamic> json) => _$SlideFromJson(json);

  Map<String, dynamic> toJson() => _$SlideToJson(this);
}