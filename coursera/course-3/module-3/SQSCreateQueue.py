import boto3

# Get the device resource
sqs = boto3.resource('sqs')

# Cria a queue
queue = sqs.create_queue(QueueName='teste', Attributes={'DelaySeconds':'5'})

# Podemos agora acessar os identifiers e atributos
print(queue.url)
print(queue.attributes.get('DelaySeconds'))
