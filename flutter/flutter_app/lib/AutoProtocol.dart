import 'package:json_annotation/json_annotation.dart';

part 'AutoProtocol.g.dart';

@JsonSerializable()
class AutoProtocol{
  AutoProtocol(this.name, this.id);

  String name;
  int id;

  factory AutoProtocol.fromJson(Map<String, dynamic> json) => _$AutoProtocolFromJson(json);

  Map<String, dynamic> toJson() => _$AutoProtocolToJson(this);
}
