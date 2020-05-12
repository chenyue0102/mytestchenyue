
class TestProtocol{
  TestProtocol(this.name, this.id);

  String name;
  int id;

  TestProtocol.fromJson(Map<String, dynamic> json)
      :name = json['name'],
      id = json['id'];

  Map<String, dynamic> toJson() =>
      <String, dynamic>{
        'name':name,
        'id':id,
      };
}
