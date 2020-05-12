import 'package:analyzer/dart/element/element.dart';
import 'package:source_gen/source_gen.dart';
import 'package:build/build.dart';


class TestMeta{
  const TestMeta(this.URL);
  final String URL;
}

class TestGenerator extends GeneratorForAnnotation<TestMeta>{
  @override
  generateForAnnotatedElement(Element element, ConstantReader constantReader, BuildStep buildStep){
    return "";
  }
}

Builder testBuilder(BuilderOptions options) => LibraryBuilder(TestGenerator());